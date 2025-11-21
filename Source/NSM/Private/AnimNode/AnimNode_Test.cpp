#include "AnimNode/AnimNode_Test.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/Rig.h"
#include "AnimationRuntime.h"
#include "Core/NeuralNetwork.h"
#include "Components/TrajectoryComponent.h"
#include "Utility/AnimInstanceMotionMatching.h"

void FAnimNode_Test::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
    FAnimNode_Base::Initialize_AnyThread(Context);
    GetEvaluateGraphExposedInputs().Execute(Context);

    // Getting a trajectory component
    Owner = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOwner();

    NumberOfJoints = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetNumBones();
}

void FAnimNode_Test::Update_AnyThread(const FAnimationUpdateContext& Context)
{
    GetEvaluateGraphExposedInputs().Execute(Context);
    ATestPawn* Pawn = Cast<ATestPawn>(Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOwner());
    if (Pawn) {
        OriginalRotations = Pawn->OriginalRotations;
        RootRotation = Pawn->GeneralRootRotation;
        Joints = Pawn->Joints;

        AnimInstance = Cast<UAnimInstanceMotionMatching>(Pawn->GetSkeleton()->GetAnimInstance());
    }

}


void FAnimNode_Test::Evaluate_AnyThread(FPoseContext& Output)
{

    Output.Pose.ResetToRefPose();

    if (!ensure(NNConfig.Rig && NNConfig.BoneMappingTable.Num() > 0)) return;
    if (OriginalRotations.Num() <= 0) return;


    const FBoneContainer& BoneContainer = Output.AnimInstanceProxy->GetRequiredBones();
    if (BoneContainer.GetNumBones() == NumberOfJoints)
    {
        FCompactPose& TargetPose = Output.Pose;

        const TArray<FNode>& Nodes = NNConfig.Rig->GetNodes();
        USkeletalMesh* CharacterMesh = BoneContainer.GetSkeletalMeshAsset();

        for (auto Node : Nodes)
        {
            if (Node.bAdvanced)continue;
            if (NNConfig.BoneMappingTable[Node.Name] == -1 || !NNConfig.BoneMappingTable.Contains(Node.Name)) continue;

            FName BoneName = CharacterMesh->Skeleton->GetRigBoneMapping(Node.Name);

            FBoneReference BoneReference(BoneName);
            BoneReference.Initialize(BoneContainer);

            if (BoneName.IsNone())continue;

            if (Node.DisplayName.Equals("Root")) {

                FQuat ResultRotation =
                    FRotator(
                        OriginalRotations[BoneContainer.GetPoseBoneIndexForBoneName(BoneName)].Rotator().Yaw,
                        -OriginalRotations[BoneContainer.GetPoseBoneIndexForBoneName(BoneName)].Rotator().Pitch,
                        OriginalRotations[BoneContainer.GetPoseBoneIndexForBoneName(BoneName)].Rotator().Roll - 90
                    ).Quaternion();
                ResultRotation = RootRotation * ResultRotation;
                ResultRotation.Normalize();

                TargetPose[BoneReference.GetCompactPoseIndex(BoneContainer)] = FTransform(ResultRotation);

            }
            else if (NNConfig.BoneMappingTable[Node.Name] != -1) {
                FName ParentBoneName = CharacterMesh->Skeleton->GetRigBoneMapping(Node.ParentName);
                FQuat ResultRotation = OriginalRotations[BoneContainer.GetPoseBoneIndexForBoneName(ParentBoneName)].Inverse() * OriginalRotations[BoneContainer.GetPoseBoneIndexForBoneName(BoneName)];
                ResultRotation =
                    FRotator(
                        ResultRotation.Rotator().Pitch,
                        -ResultRotation.Rotator().Yaw,
                        -ResultRotation.Rotator().Roll
                    ).Quaternion();

                FVector ResultLocation = CharacterMesh->RetargetBasePose[BoneContainer.GetPoseBoneIndexForBoneName(BoneName)].GetLocation(); 
                if (Node.Name.IsEqual("Pelvis")) {
                    ResultLocation = Joints[NNConfig.BoneMappingTable[Node.Name]].Location - Joints[NNConfig.BoneMappingTable[Node.ParentName]].Location;
                    ResultLocation.Y = -ResultLocation.Y;
                }
                TargetPose[BoneReference.GetCompactPoseIndex(BoneContainer)] = FTransform(ResultRotation, ResultLocation);
            }
        }

        if (AnimInstance) {
            FBoneReference BoneReference("foot_l");
            BoneReference.Initialize(BoneContainer);
            AnimInstance->LeftFoot = GetBoneWorldLocation(BoneReference.GetCompactPoseIndex(BoneContainer), TargetPose);

            BoneReference = FBoneReference("foot_r");
            BoneReference.Initialize(BoneContainer);
            AnimInstance->RightFoot = GetBoneWorldLocation(BoneReference.GetCompactPoseIndex(BoneContainer), TargetPose);

            BoneReference = FBoneReference("ball_l");
            BoneReference.Initialize(BoneContainer);
            AnimInstance->LeftToe = GetBoneWorldLocation(BoneReference.GetCompactPoseIndex(BoneContainer), TargetPose);

            BoneReference = FBoneReference("ball_r");
            BoneReference.Initialize(BoneContainer);
            AnimInstance->RightToe = GetBoneWorldLocation(BoneReference.GetCompactPoseIndex(BoneContainer), TargetPose);

        }

    }

}

FTransform FAnimNode_Test::GetBoneWorldLocation(FCompactPoseBoneIndex CompactBoneIndex, FCompactPose& TargetPose)
{
    if (CompactBoneIndex.IsRootBone()) {
        return TargetPose[CompactBoneIndex];
    }
    FCompactPoseBoneIndex ParentCompactBoneIndex  = TargetPose.GetParentBoneIndex(CompactBoneIndex);

    return TargetPose[CompactBoneIndex] *  GetBoneWorldLocation(ParentCompactBoneIndex, TargetPose);
}
