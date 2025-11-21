// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PFNNAnimInstance.h"

void UPFNNAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    NeuralNetwork = NewObject<UNeuralNetwork>();
    if (NeuralNetwork)
    {
        NeuralNetwork->LoadModel();
    }
}
