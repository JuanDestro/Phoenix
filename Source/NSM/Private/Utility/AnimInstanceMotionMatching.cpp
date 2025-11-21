// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/AnimInstanceMotionMatching.h"

#include "Kismet/KismetMathLibrary.h"

UAnimInstanceMotionMatching::UAnimInstanceMotionMatching()
{
    JoinTargetLeft = FVector(50.f, 217.50296f, -38.598057f);
    JoinTargetRight = FVector(50.f, 217.f, 38.f);
    LeftFootOut = false;
    RightFootOut = false;
}

void UAnimInstanceMotionMatching::SetLeftEffectorLocation(FVector NewEffectorLocation)
{
    if (! (LeftFootEffectorLocation - NewEffectorLocation).IsNearlyZero(0.01))
    {
        LeftFootEffectorLocation = NewEffectorLocation;
    }
}

void UAnimInstanceMotionMatching::SetRightEffectorLocation(FVector NewEffectorLocation)
{
    if (! (RightFootEffectorLocation - NewEffectorLocation).IsNearlyZero(0.01))
    {
        RightFootEffectorLocation = NewEffectorLocation;
    }    
}

void UAnimInstanceMotionMatching::SetLeftFootAlpha(float NewAlpha)
{
    LeftFootAlpha = NewAlpha;
}

void UAnimInstanceMotionMatching::SetRightFootAlpha(float NewAlpha)
{
    RightFootAlpha = NewAlpha;
}

void UAnimInstanceMotionMatching::SetLeftFootOut(bool NewValue)
{
    LeftFootOut = NewValue;
}

void UAnimInstanceMotionMatching::SetRightFootOut(bool NewValue)
{
    RightFootOut = NewValue;
}

void UAnimInstanceMotionMatching::SetLeftFootRotation(FRotator NewValue)
{
    if (! (LeftFootRotation - NewValue).IsNearlyZero(0.01))
    {   
        LeftFootRotation = NewValue;
    }
}

void UAnimInstanceMotionMatching::SetRightFootRotation(FRotator NewValue)
{
    if (! (LeftFootRotation - NewValue).IsNearlyZero(0.01))
    {   
        RightFootRotation = NewValue;
    }    
}

void UAnimInstanceMotionMatching::SetAimTarget(FRotator AimTarget, float DeltaTime)
{
    const FRotator NewAim = UKismetMathLibrary::RInterpTo(FRotator(AimPitch, AimYaw, 0), AimTarget, DeltaTime, 5.0f);
    AimYaw = FMath::ClampAngle(NewAim.Yaw, -80.f, 80.0f);
    AimPitch = FMath::ClampAngle(NewAim.Pitch, -80.f, 80.0f);
}
