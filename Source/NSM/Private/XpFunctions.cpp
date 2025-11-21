// Fill out your copyright notice in the Description page of Project Settings.


#include "XpFunctions.h"

void UXpFunctions::CalledFromPython(FString InputString) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InputString);
}

