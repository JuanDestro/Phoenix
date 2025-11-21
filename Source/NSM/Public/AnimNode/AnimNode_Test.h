#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNodeBase.h"
#include "Containers/StaticArray.h"
#include "Core/TestPawn.h"
#include "AnimNode_Test.generated.h"


USTRUCT(BlueprintType)
struct FNNRigConfiguration
{
    GENERATED_USTRUCT_BODY()

        UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class URig* Rig;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        TMap<FName, int32> BoneMappingTable;
};

USTRUCT(BlueprintType)
struct NSM_API FAnimNode_Test : public FAnimNode_Base
{
    GENERATED_BODY()

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinHiddenByDefault))
    //class UNeuralNetwork* NeuralNetwork = nullptr;
    //
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinHiddenByDefault))
    //class UTrajectoryComponent* TrajectoryComponent = nullptr;
    
    UPROPERTY(Category = Character, EditDefaultsOnly, BlueprintReadOnly, meta =(NeverAsPin))
    FNNRigConfiguration NNConfig;

    TArray<FQuat> OriginalRotations;
    TArray<FJointTransform> Joints;
    FQuat RootRotation;
    AActor* Owner = nullptr;
    
    int32 NumberOfJoints;
    class UAnimInstanceMotionMatching* AnimInstance = nullptr;

    FTransform GetBoneWorldLocation(FCompactPoseBoneIndex CompactBoneIndex, FCompactPose& TargetPose);

public:

    // FAnimNode_Base interface
    virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
    virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
    virtual void Evaluate_AnyThread(FPoseContext & Output) override;
    // End of FAnimNode_Base interface
};
