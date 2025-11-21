#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IKUtilities.generated.h"

class UAnimInstanceMotionMatching;
UCLASS()
class NSM_API UIKUtilities : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    static bool LeftFootContact;
    static bool RightFootContact;

    static FVector PastFootLocationLeft;
    static FVector PastFootLocationRight;

    static TArray<float> LeftSpeeds;

public:
    //
    // IK
    //

    /** Gets feet rotation from a given normal */
    static FRotator GetRotationFromNormal(FVector Normal);

    /** Calculates Foot IK */
    // TODO: Move to Shared
    // TODO: Remove mutations inside function
    // TODO: Remove UAnimInstanceMotionMatching dependency
    static void CalculateFootIK(
        UAnimInstanceMotionMatching* FPAnim, FVector GetVelocity, USkeletalMeshComponent* SkeletalMesh, FName LeftFootBoneName,
        FName RightFootBoneName, FVector LeftJointTargetLocation, FVector RightJointTargetLocation, bool& HasTakenIdlePosition, float LeftAlpha, float RightAlpha,
        float& AccumulatedTime, float LeftDeltaFeetDistance, float RightDeltaFeetDistance, float InterpolationSpeedIk, AActor* WorldContextObject
    );
};