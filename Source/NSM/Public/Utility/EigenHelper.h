#pragma once

#include "../ThirdParty/EigenLib/Eigen.h"

typedef Eigen::ArrayXf Vector;
typedef Eigen::ArrayXXf Matrix;

struct FEigenHelper
{
    static void ELU(Vector& X)
    {
        X = X.max(0) + X.min(0).exp() - 1;
    }

    template<typename TValue>
    static void Linear(TValue& O, const TValue& Y0, const TValue& Y1, float Mu)
    {
        O = ( 1.0f - Mu ) * Y0 + Mu * Y1;
    }

    template<typename TValue>
    static void Cubic(TValue& O, const TValue& Y0, const TValue& Y1, const TValue& Y2, const TValue& Y3, float Mu)
    {
        O = ( 0.5f *Y0 + 1.5f * Y1 - 1.5f * Y2 + 0.5f * Y3 ) * FastPow3(Mu) + 
          ( Y0 - 2.5f * Y1 + 2.0f * Y2 - 0.5f * Y3 ) * FastPow2(Mu) + 
          ( -0.5f * Y0 + 0.5f * Y2 ) * Mu + Y1 ;
    }

private:
    static float FastPow3(float& Value)
    {
        return Value * Value * Value;
    }
    static float FastPow2(float& Value)
    {
        return Value;
    }
};
