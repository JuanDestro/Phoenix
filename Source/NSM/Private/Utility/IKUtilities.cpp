
#include "Utility/IKUtilities.h"
#include "Utility/AnimInstanceMotionMatching.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

bool UIKUtilities::LeftFootContact = false;
bool UIKUtilities::RightFootContact = false;

FVector UIKUtilities::PastFootLocationLeft = FVector::ZeroVector;
FVector UIKUtilities::PastFootLocationRight = FVector::ZeroVector;

FRotator UIKUtilities::GetRotationFromNormal(FVector Normal)
{
	return FRotator(			
		0,
		UKismetMathLibrary::DegAtan2(Normal.X, Normal.Z) * -1.0f,
		UKismetMathLibrary::DegAtan2(Normal.Y, Normal.Z)    
    );
}

void UIKUtilities::CalculateFootIK(
	UAnimInstanceMotionMatching* FPAnim, FVector GetVelocity, USkeletalMeshComponent* SkeletalMesh, FName LeftFootBoneName,
	FName RightFootBoneName, FVector LeftJointTargetLocation, FVector RightJointTargetLocation, bool& HasTakenIdlePosition, float LeftAlphaTest, float RightAlphaTest,
	float& AccumulatedTime, float LeftDeltaFeetDistance, float RightDeltaFeetDistance, float InterpolationSpeedIk, AActor* WorldContextObject
)
{
	// Check Location of the floor under the feet
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add((AActor*)WorldContextObject);

	FHitResult LeftTraceHit;
	FVector LeftFootLocation = (FPAnim->LeftFoot * SkeletalMesh->GetRelativeTransform() * WorldContextObject->GetActorTransform()).GetLocation();
	bool bLeftFootTraceHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, LeftFootLocation + FVector(0.f, 0.f, 100.f),
		LeftFootLocation + FVector(0.f, 0.f, -100.f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame,
		LeftTraceHit, true);

	LeftFootLocation.Z -= LeftDeltaFeetDistance;


	float LeftSpeed = (LeftFootLocation - PastFootLocationLeft).SizeSquared();
	PastFootLocationLeft = LeftFootLocation;
	float LeftAlpha = FMath::Clamp(-0.25f * (LeftFootLocation.Z - LeftTraceHit.ImpactPoint.Z) + 1.25f, 0.f, 1.f);
	
	FHitResult RightTraceHit;
	FVector RightFootLocation = (FPAnim->RightFoot * SkeletalMesh->GetRelativeTransform() * WorldContextObject->GetActorTransform()).GetLocation();;
	bool bRightFootTraceHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, RightFootLocation + FVector(0.f, 0.f, 100.f),
		RightFootLocation + FVector(0.f, 0.f, -100.f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame,
		RightTraceHit, true);

	RightFootLocation.Z -= RightDeltaFeetDistance;

	float RightSpeed = (RightFootLocation - PastFootLocationRight).SizeSquared();
	PastFootLocationRight = RightFootLocation;
	float RightAlpha = FMath::Clamp(-0.25f * (RightFootLocation.Z - RightTraceHit.ImpactPoint.Z) + 1.25f, 0.f, 1.f);
	

	bool LeftContactBefore = LeftFootContact;
	bool RightContactBefore = RightFootContact;

	LeftFootContact = LeftAlpha >= 0.5f && LeftSpeed < 5.f;
	RightFootContact = RightAlpha >= 0.5f && RightSpeed < 5.f;

	FPAnim->SetLeftFootAlpha(FMath::Lerp(FPAnim->GetLeftFootAlpha(),(float)LeftAlphaTest, 0.9));
	FPAnim->SetRightFootAlpha(FMath::Lerp(FPAnim->GetRightFootAlpha(), (float)RightAlphaTest, 0.9));

	if (LeftAlphaTest < 0.5f) {
		FVector LeftImpactPoint = FVector(LeftTraceHit.ImpactPoint.X, LeftTraceHit.ImpactPoint.Y, LeftTraceHit.ImpactPoint.Z + LeftDeltaFeetDistance);
		FPAnim->SetLeftEffectorLocation(LeftImpactPoint);
		FPAnim->SetJointTargetLeft(LeftJointTargetLocation);
	}

	if (RightAlphaTest < 0.5f) {

		FVector RightImpactPoint = FVector(RightTraceHit.ImpactPoint.X, RightTraceHit.ImpactPoint.Y, RightTraceHit.ImpactPoint.Z + RightDeltaFeetDistance);
		FPAnim->SetRightEffectorLocation(RightImpactPoint);
		FPAnim->SetJointTargetRight(RightJointTargetLocation);
	}

	//if(GetVelocity.Size() > 0.1f)
	//{
	//}
	//else if (!HasTakenIdlePosition)
	//{
	//	if (AccumulatedTime < 1.2f)
	//	{
	//		AccumulatedTime += DeltaTime;
	//	}
	//	else
	//	{
	//		const FVector LeftFootBoneWorldLocation = GetMesh->GetBoneLocation(LeftFootBoneName);
	//		LeftFootBoneRelativeLocation = GetActorTransform.InverseTransformPosition(LeftFootBoneWorldLocation);

	//		const FVector RightFootBoneWorldLocation = GetMesh->GetBoneLocation(RightFootBoneName);
	//		RightFootBoneRelativeLocation = GetActorTransform.InverseTransformPosition(RightFootBoneWorldLocation);

	//		InitialMeshRelativeLocation = GetMesh->GetRelativeTransform().GetLocation();
 //       	
	//		HasTakenIdlePosition = true;
	//	}
	//}
	//
	//// Feet location
	//if (!HasTakenIdlePosition)
	//{
	//	FPAnim->SetLeftFootAlpha(0.f);
	//	FPAnim->SetRightFootAlpha(0.f);
	//}
	//else
	//{
	//	TArray<AActor*> ActorsToIgnore;
	//	ActorsToIgnore.Add((AActor*)WorldContextObject);

	//	FHitResult LeftTraceHit;
	//	const FVector LeftFootLocation = GetTransform.TransformPosition(CurrentLeft);
	//	bool bLeftFootTraceHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, LeftFootLocation + FVector(0.f, 0.f, 100.f),
	//		LeftFootLocation + FVector(0.f, 0.f, -100.f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame,
	//		LeftTraceHit, true);

	//	FHitResult RightTraceHit;
	//	const FVector RightFootLocation = GetTransform.TransformPosition(CurrentRight);
	//	bool bRightFootTraceHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, RightFootLocation + FVector(0.f, 0.f, 100.f),
	//		RightFootLocation + FVector(0.f, 0.f, -100.f), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame,
	//		RightTraceHit, true);

	//}
}
