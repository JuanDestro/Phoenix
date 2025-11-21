// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Core/NeuralNetwork.h"

#include "PFNNAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NSM_API UPFNNAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPFNNAnimInstance() = default;

	UPROPERTY()
	TArray<FJointTransform> Joints;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UNeuralNetwork* NeuralNetwork;

	virtual void NativeBeginPlay() override;
	
};

