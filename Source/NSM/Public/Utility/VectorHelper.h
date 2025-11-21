#pragma once
#include "CoreMinimal.h"

struct FVectorHelper
{
    static FVector MakeFromLeftHanded(const FVector& Vector)
    {
        return FVector(Vector.Z, Vector.X, Vector.Y);
    }

    static FVector MakeFromLeftHanded(float X, float Y, float Z)
    {
        return FVector(Z, X, Y);
    }
};
