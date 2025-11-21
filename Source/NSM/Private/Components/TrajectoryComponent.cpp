// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TrajectoryComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utility/EigenHelper.h"
#include "Utility/QuatHelper.h"
#include "Utility/VectorHelper.h"

UTrajectoryComponent::UTrajectoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    TargetDirection = FVector::ForwardVector;
    TargetVelocity = FVector::ZeroVector;
	TrajectoryLength = 120;//120 when training is 60, 240 when trainging is 120
	RayCastLength = 1000.0f;
	RayCastInitialHeight = 600.0f;
	MovementSpeed = 5.0f;
	TrajectoryDisplayOffsets = FVector(0, 0, 35.0f);
}

void UTrajectoryComponent::BeginPlay()
{
    Super::BeginPlay();
    check(GetOwner());
    OwnerPawn = Cast<APawn>(GetOwner());
	InitializeTrajectoryPoints();
	InitializeMovementStyles();
	RootIndex = TrajectoryLength / 2;
}

void UTrajectoryComponent::InitializeTrajectoryPoints()
{
	TrajectoryPoints.Init(FTrajectoryPoint(), TrajectoryLength);
}

void UTrajectoryComponent::InitializeMovementStyles()
{
	MovementStyles.Init(FMovementStyle(), TrajectoryLength);
}

//TODO: Input without Z
void UTrajectoryComponent::UpdateTargetDirectionAndVelocity(FVector NewTargetDirection, float AxisX, float AxisY)
{
	//TODO: Adjust movement speed
    const FVector NewTargetVelocity =  MovementSpeed * FVector(AxisX, AxisY, 0.0f);
	
    TargetVelocity = UKismetMathLibrary::VLerp(TargetVelocity, NewTargetVelocity, ExtraVelocitySmooth);
    const FVector TargetVelocityDirection = FMath::IsNearlyZero(TargetVelocity.Size(), 1e-05f)
	                                            ? TargetDirection
	                                            : TargetVelocity.GetSafeNormal();

    NewTargetDirection = FQuatHelper::MixDirections(TargetVelocityDirection, NewTargetDirection, 0.0);
    TargetDirection = FQuatHelper::MixDirections(TargetDirection, NewTargetDirection, ExtraVelocitySmooth);
}

void UTrajectoryComponent::UpdateMovementStyle(EMovementType InputStyle)
{
	//TODO: Other movements
	if (TargetVelocity.Size() < 0.1f)
	{
		// Idle
        const float StandAmount = 1.0f - FMath::Clamp(TargetVelocity.Size() / 0.1f, 0.0f, 1.0f);
		MovementStyles[RootIndex].UpdateMovementType(EMovementType::Stand, StandAmount);
    }
	else
	{
		// Walk
		MovementStyles[RootIndex].UpdateMovementType(InputStyle, 1.0f);
    }
}

void UTrajectoryComponent::PredictFutureTrajectory()
{
    TArray<FVector> BlendingLocations;
	BlendingLocations.Init(FVector::ZeroVector, TrajectoryLength);	
    BlendingLocations[RootIndex] = TrajectoryPoints[RootIndex].Location;

	FVector PreviousLocation = TrajectoryPoints[RootIndex].Location;
		
    const float LocationInfluence = UKismetMathLibrary::Lerp(0.5f, 1.0f, 0);
    const float DirectionInfluence = UKismetMathLibrary::Lerp(2.0f, 0.5f, 0);
	
    for (int i = RootIndex + 1; i < TrajectoryLength; i++)
    {
    	// Calculate the amount of movement and rotation that the point in the trajectory can apply depending on the distance to the root
    	const float PercentageDistance = static_cast<float>(i - RootIndex) / RootIndex;
        const float LocationScale = 1.0f - FMath::Pow(1.0f - PercentageDistance, LocationInfluence);
        const float DirectionScale = 1.0f - FMath::Pow(1.0f - PercentageDistance, DirectionInfluence);

        BlendingLocations[i] = BlendingLocations[i - 1] + UKismetMathLibrary::VLerp(
            TrajectoryPoints[i].Location - PreviousLocation, TargetVelocity, LocationScale);

    	/*PENDING COLLIDE WALLS*/
    	
        TrajectoryPoints[i].Direction = FQuatHelper::MixDirections(TrajectoryPoints[i].Direction, TargetDirection, DirectionScale);
    	TrajectoryPoints[i].Height = TrajectoryPoints[RootIndex].Height;

    	// Apply root movement style to the future points
    	MovementStyles[i].CopyFrom(MovementStyles[RootIndex]);

    	//Take a copy of the current location
    	PreviousLocation = TrajectoryPoints[i].Location;

    	TrajectoryPoints[i].Location = BlendingLocations[i];
    }
}

void UTrajectoryComponent::UpdateRotations()
{
    for (int i = 0; i < TrajectoryLength; i++)
    {
	    TrajectoryPoints[i].Rotation = CalculateDirection(TrajectoryPoints[i].Direction.Y,
	                                                      TrajectoryPoints[i].Direction.X);
    }
}

void UTrajectoryComponent::UpdateHeights()
{
	for (int i = RootIndex; i < TrajectoryLength; ++i)
	{
		TrajectoryPoints[i].Location.Z = GetHeightSample(TrajectoryPoints[i].Location);
	}

	const float ImportantPoints = TrajectoryLength / 10;
	TrajectoryPoints[RootIndex].Height = 0.0f;
	for (int i = 0; i < TrajectoryLength; i += 10)
	{
		TrajectoryPoints[RootIndex].Height += TrajectoryPoints[i].Location.Z / ImportantPoints;
	}
}

float UTrajectoryComponent::GetHeightSample(const FVector& Location) const
{
	const TArray<AActor*> IgnoredActors { OwnerPawn };
	FHitResult HitResult;
	// Arbitrary values
	const FVector InitialLocation = Location + FVector::UpVector * RayCastInitialHeight;
	const FVector EndLocation =  Location + FVector::UpVector * -RayCastLength;
	const bool bHitSomething = UKismetSystemLibrary::LineTraceSingle(GetWorld(), InitialLocation, EndLocation,
	                                                                 UEngineTypes::ConvertToTraceType(ECC_Visibility),
	                                                                 false, IgnoredActors,
	                                                                 EDrawDebugTrace::None, HitResult, true);
	if (bHitSomething)
	{
		return HitResult.Location.Z;
	}
	return 0.0f;
}

void UTrajectoryComponent::PostVisualisationCalculation(const Vector& Y)
{
	for (int i = 0; i < RootIndex; ++i)
	{
		TrajectoryPoints[i].Location = TrajectoryPoints[i + 1].Location;
		TrajectoryPoints[i].Rotation = TrajectoryPoints[i + 1].Rotation;
		TrajectoryPoints[i].Direction = TrajectoryPoints[i + 1].Direction;
		TrajectoryPoints[i].Height = TrajectoryPoints[i + 1].Height;
		MovementStyles[i].CopyFrom(MovementStyles[i + 1]);
	}

	const float StandAmount = GetStandAmount();
	const FVector TrajectoryUpdate = TrajectoryPoints[RootIndex].Rotation * FVectorHelper::MakeFromLeftHanded(Y[0], 0.0f, Y[1]);
	TrajectoryPoints[RootIndex].Location = TrajectoryPoints[RootIndex].Location + StandAmount * TrajectoryUpdate;
	TrajectoryPoints[RootIndex].Direction = FQuat(FVector::UpVector,
		StandAmount * -Y[2]) * TrajectoryPoints[RootIndex].Direction;
	
	if (FMath::IsNearlyZero(TrajectoryPoints[RootIndex].Direction.Size()))
	{
		TrajectoryPoints[RootIndex].Direction =  FVector::ForwardVector;	
	}
	 
	TrajectoryPoints[RootIndex].Rotation = CalculateDirection(TrajectoryPoints[RootIndex].Direction.Y, TrajectoryPoints[RootIndex].Direction.X);
		
	const int W = RootIndex / 10;
	for (int i = RootIndex + 1; i < TrajectoryLength; ++i)
	{
		// Move this to NN
		// Locations relative to root
		TrajectoryPoints[i].Location.Y  = Y[8 + (W * 0) + (i / 10) - W];
		TrajectoryPoints[i].Location.X  = Y[8 + (W * 1) + (i / 10) - W];
		TrajectoryPoints[i].Direction.Y = Y[8 + (W * 2) + (i / 10) - W];
		TrajectoryPoints[i].Direction.X = Y[8 + (W * 3) + (i / 10) - W];

		TrajectoryPoints[i].Location = TrajectoryPoints[RootIndex].Rotation * TrajectoryPoints[i].Location + TrajectoryPoints[RootIndex].Location;
		TrajectoryPoints[i].Direction = (TrajectoryPoints[RootIndex].Rotation * TrajectoryPoints[i].Direction).GetSafeNormal();
		TrajectoryPoints[i].Rotation = CalculateDirection(TrajectoryPoints[i].Direction.Y, TrajectoryPoints[i].Direction.X);		
	}
}

void UTrajectoryComponent::DisplayTrajectory()
{
	for (int i = 0; i < TrajectoryLength; ++i)
	{
		DrawDebugPoint(GetWorld(), TrajectoryPoints[i].Location + TrajectoryDisplayOffsets,
		               13.0f, FColor::Yellow);
	}
}

FQuat UTrajectoryComponent::CalculateDirection(const float& Y, const float& X)
{
	return FQuat(FVector::UpVector,
	             FMath::Atan2(Y, X));
}


DEFINE_STAT(STAT_NNTrajectory);
void UTrajectoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	SCOPE_CYCLE_COUNTER(STAT_NNTrajectory);
	
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Camera)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no camera component."))
		return;
	}
	
	FVector Input = OwnerPawn->ConsumeMovementInputVector();
	Input.Z = 0.0f;
	Input.Normalize();
    StrafeAmount = 0.0f;

    FVector NewTargetDirection = Camera->GetForwardVector();	      
    NewTargetDirection.Z = 0.0f;
    NewTargetDirection.Normalize();

    UpdateTargetDirectionAndVelocity(NewTargetDirection, Input.X, Input.Y);
	UpdateMovementStyle(InputWalk);
    PredictFutureTrajectory();	

	UpdateRotations();
	UpdateHeights();

	DisplayTrajectory();
	
}

float UTrajectoryComponent::GetStandAmount()
{
	// Review this
	return FMath::Pow(1.0f - MovementStyles[TrajectoryLength / 2].Values[(int)EMovementType::Stand], 0.25f);
}
