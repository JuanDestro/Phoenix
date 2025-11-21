#pragma once
#include "CoreMinimal.h"

struct FQuatHelper
{
    static FVector MixDirections(const FVector& XDirection, const FVector& YDirection, const float Scalar)
    {
        const FQuat XQuat = FQuat(FVector::UpVector, FMath::Atan2(XDirection.Y, XDirection.X));
        const FQuat YQuat = FQuat(FVector::UpVector, FMath::Atan2(YDirection.Y, YDirection.X));
        const FQuat ZQuat = FQuat::Slerp(XQuat, YQuat, Scalar);
        return ZQuat * FVector::ForwardVector;
    }

    static FQuat QuaternionExponent(FVector Vector)
    {
        const float Magnitude = Vector.Size();
        
        const FQuat Quat = Magnitude < 0.01f ? FQuat::Identity : FQuat(
            Vector.X * (FMath::Sin(Magnitude) / Magnitude),
            Vector.Y * (FMath::Sin(Magnitude) / Magnitude),
            Vector.Z * (FMath::Sin(Magnitude) / Magnitude),
            FMath::Cos(Magnitude));
        
        return Quat.GetNormalized();
    }
};
