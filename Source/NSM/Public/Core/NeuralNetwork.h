// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TrajectoryComponent.h"
#include "Core/TestPawn.h"
#include "UObject/NoExportTypes.h"
#include "Utility/EigenHelper.h"
#include "NeuralNetwork.generated.h"


const int XDIM = 569, YDIM = 644, HDIM = 512;
enum { MODE_CONSTANT, MODE_LINEAR, MODE_CUBIC };

/**
 * 
 */
UCLASS(Blueprintable)
class NSM_API UNeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
    UNeuralNetwork();

	void LoadModel();
	
public:	
    int Mode;

	float Phase;
    
	Vector Xmean, Xstd;
    
	Vector Ymean, Ystd;
  
	TArray<Matrix> W0, W1, W2;
	TArray<Vector>  B0, B1, B2;
  
	Vector  Xp, Yp;
	Vector  H0,  H1;
	Matrix	W0p, W1p, W2p;
	Vector  B0p, B1p, B2p;

	void UpdatePhase(float StandAmount);

	void Predict();

	void UpdateNetworkInput(UTrajectoryComponent* TrajectoryComponent, const TArray<FJointTransform>& Joints, FVector RootVelocity, FVector RootAccel);

protected:
	void LoadWeights(Vector& InVector, int Cols, FString FileName);

	void LoadWeights(Matrix& InMatrix, int Rows, int Cols, FString FileName);

	FString GetSuffix(int& Value);

	
};
