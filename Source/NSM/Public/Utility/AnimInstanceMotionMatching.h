// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceMotionMatching.generated.h"

/**
 * 
 */
UCLASS()
class NSM_API UAnimInstanceMotionMatching : public UAnimInstance
{
	GENERATED_BODY()

public:
	FTransform LeftFoot;
	FTransform RightFoot;

	FTransform LeftToe;
	FTransform RightToe;

	UAnimInstanceMotionMatching();

	void SetLeftEffectorLocation(FVector NewEffectorLocation);
	FVector GetLeftEffectorLocation() { return LeftFootEffectorLocation; }

	void SetRightEffectorLocation(FVector NewEffectorLocation);
	FVector GetRightEffectorLocation() { return RightFootEffectorLocation; }

	void SetLeftFootAlpha(float NewAlpha);
	float GetLeftFootAlpha() { return LeftFootAlpha; }

	void SetRightFootAlpha(float NewAlpha);
	float GetRightFootAlpha() { return RightFootAlpha; }

	void SetJointTargetLeft(FVector JointTarget) { JoinTargetLeft = JointTarget; }
	void SetJointTargetRight(FVector JointTarget) { JoinTargetRight = JointTarget; }

	void SetLeftFootOut(bool NewValue);
	
	void SetRightFootOut(bool NewValue);
	
	void SetLeftFootRotation(FRotator NewValue);
	
	void SetRightFootRotation(FRotator NewValue);

	void SetAimTarget(FRotator AimTarget, float DeltaTime);

protected:
	/** Left foot effector location */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=IK , meta=(BlueprintProtected = true))
	FVector LeftFootEffectorLocation;

	/** Joint target left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	FVector JoinTargetLeft;

	/** Left foot alpha*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	float LeftFootAlpha;

	/** Right foot effector location */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	FVector RightFootEffectorLocation;

	/** Joint target right*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	FVector JoinTargetRight;

	/** right foot alpha*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	float RightFootAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	bool LeftFootOut;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	bool RightFootOut;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	FRotator LeftFootRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= IK , meta = (BlueprintProtected = true))
	FRotator RightFootRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= AIM , meta = (BlueprintProtected = true))
	float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= AIM , meta = (BlueprintProtected = true))
	float AimPitch;
};
