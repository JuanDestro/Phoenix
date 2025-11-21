// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/StaticArray.h"
#include "Utility/EigenHelper.h"
#include "TrajectoryComponent.generated.h"


DECLARE_STATS_GROUP(TEXT("NNTrajectory"), STATGROUP_NNTrajectory, STATCAT_Advanced);

DECLARE_CYCLE_STAT_EXTERN(TEXT("NNTrajectory"), STAT_NNTrajectory, STATGROUP_NNTrajectory, NSM_API);

static float ExtraDirectionSmooth = 0.9f;
static float ExtraVelocitySmooth = 0.9f;
static float ExtraStrafeSmooth = 0.9f;
static float ExtraCrouchedSmooth = 0.9f;
static float ExtraMovementStyleSmooth = 0.1f;
static float ExtraJointSmooth = 0.5f;

struct FTrajectoryPoint
{
    FQuat Rotation;
    FVector Location;
    FVector Direction;
    float Height;

    FTrajectoryPoint()
        : Rotation(FQuat::Identity), Location(FVector::ZeroVector), Direction(FVector::ForwardVector), Height(0.0f)
    {
    }
};

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    Stand,
    Walk,
    Jog,
    Run,
    Crouch,
    Jump,
    Bump
};

struct FMovementStyle
{
    

    TArray<float> Values;

    void UpdateMovementType(EMovementType MovementType, float InValue)
    {
        for (int i = 0; i < Values.Num(); ++i)
        {
            if (i == (int)MovementType)
            {
                Values[i] = FMath::Lerp(Values[i], InValue, ExtraMovementStyleSmooth);
            }
            else
            {
                Values[i] = FMath::Lerp(Values[i], 0.0f, ExtraMovementStyleSmooth);
            }
        }
    }

    void CopyFrom(FMovementStyle& InMovementStyle)
    {
        for (int i = 0; i < Values.Num(); ++i)
        {
            Values[i] = InMovementStyle.Values[i];
        }
    }

    FMovementStyle()
    {
        Values.Init(0.0f, 6);
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NSM_API UTrajectoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTrajectoryComponent();

private:
    APawn* OwnerPawn;

    int RootIndex;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Trajectory")
    int TrajectoryLength;

    TArray<FTrajectoryPoint> TrajectoryPoints;

    TArray<FMovementStyle> MovementStyles;

    FVector TargetDirection;

    FVector TargetVelocity;

    float StrafeAmount;

    void InitializeTrajectoryPoints();

    void InitializeMovementStyles();

    void UpdateTargetDirectionAndVelocity(FVector NewTargetDirection, float AxisX, float AxisY);

    void UpdateMovementStyle(EMovementType InputStyle);

    void PredictFutureTrajectory();

    void UpdateRotations();

    void UpdateHeights();

    void DisplayTrajectory();

    static FQuat CalculateDirection(const float& Y, const float& X);

    UPROPERTY(EditAnywhere, Category="Trajectory")
    float RayCastInitialHeight;
    
    UPROPERTY(EditAnywhere, Category="Trajectory")
    float RayCastLength;
    
    UPROPERTY(EditAnywhere, Category="Trajectory")
    float MovementSpeed;

    UPROPERTY(EditAnywhere, Category="Trajectory")
    FVector TrajectoryDisplayOffsets;
    

public:
    
    UPROPERTY(BlueprintReadWrite)
    EMovementType InputWalk;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    float GetHeightSample(const FVector& Location) const;

    FORCEINLINE int GetTrajectoryLength() const { return TrajectoryLength; }

    FORCEINLINE TArray<FMovementStyle>& GetMovementStyles() { return MovementStyles; }

    FORCEINLINE TArray<FTrajectoryPoint>& GetTrajectoryPoints() { return TrajectoryPoints; }

    float GetStandAmount();

    void PostVisualisationCalculation(const Vector& Y);

    UPROPERTY(BlueprintReadWrite)
    class UCameraComponent* Camera;
};
