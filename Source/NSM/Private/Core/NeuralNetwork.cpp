// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NeuralNetwork.h"
#include "Components/TrajectoryComponent.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Utility/BinaryFileHelper.h"

UNeuralNetwork::UNeuralNetwork()
{
    Xp = Vector::Zero(XDIM);

    Yp = Vector::Zero(YDIM);
    
    H0 = Vector::Zero(HDIM);
    H1 = Vector::Zero(HDIM);
    
    W0p = Matrix::Zero(HDIM, XDIM);
    W1p = Matrix::Zero(HDIM, HDIM);
    W2p = Matrix::Zero(YDIM, HDIM);
    
    B0p = Vector::Zero(HDIM);
    B1p = Vector::Zero(HDIM);
    B2p = Vector::Zero(YDIM);

    Mode = MODE_CONSTANT;
    Phase = 0.0f;
}

void UNeuralNetwork::UpdatePhase(float StandAmount)
{
    Phase = FMath::Fmod(Phase + (StandAmount * 0.9f + 0.1f) * 2 * PI * Yp[3], 2 * PI);
}

//TODO: Rewrite this part to move part of the loading to FBinaryFileHelper
void UNeuralNetwork::LoadWeights(Vector& InVector, int Cols, FString FileName)
{
    FString ContentPath = FPaths::ProjectContentDir();
    FString FilePath = ContentPath + "pfnn/" + FileName;

    TArray<uint8> RawBinaryFile;
    FFileHelper::LoadFileToArray(RawBinaryFile, *FilePath);
    File FilePointer = RawBinaryFile.begin();

    InVector = Vector(Cols);
    for (int i = 0; i < Cols; ++i)
    {
        const float Value = FBinaryFileHelper::ConvertBytesToFloat(FilePointer);
        InVector(i) = Value;           
    }    
}

void UNeuralNetwork::LoadWeights(Matrix& InMatrix, int Rows, int Cols, FString FileName)
{
    FString ContentPath = FPaths::ProjectContentDir();
    FString FilePath = ContentPath + "pfnn/" + FileName;

    TArray<uint8> RawBinaryFile;
    FFileHelper::LoadFileToArray(RawBinaryFile, *FilePath);
    File FilePointer = RawBinaryFile.begin();

    InMatrix = Matrix(Rows, Cols);
    for (int x = 0; x < Rows; ++x)
    {
        for (int y = 0; y < Cols; ++ y)
        {
            const float Value = FBinaryFileHelper::ConvertBytesToFloat(FilePointer);
            InMatrix(x, y) = Value;    
        }
    }
}

void UNeuralNetwork::LoadModel()
{    
    LoadWeights(Xmean, XDIM, "Xmean.bin");
    LoadWeights(Xstd,  XDIM, "Xstd.bin" );
    LoadWeights(Ymean, YDIM, "Ymean.bin");
    LoadWeights(Ystd,  YDIM, "Ystd.bin" );

    switch (Mode)
    {
        case MODE_CONSTANT:
            Matrix DefaultMatrix = Matrix(1,1);
            W0.SetNum(50);
            W1.SetNum(50);
            W2.SetNum(50);
            B0.SetNum(50);
            B1.SetNum(50);
            B2.SetNum(50);

        for (int i = 0; i < 50; ++i)
        {
            FString Suffix = GetSuffix(i);
            LoadWeights(W0[i], HDIM, XDIM, "W0_" + Suffix);
            LoadWeights(W1[i], HDIM, HDIM, "W1_" + Suffix);
            LoadWeights(W2[i], YDIM, HDIM, "W2_" + Suffix);
            LoadWeights(B0[i], HDIM, "b0_" + Suffix);
            LoadWeights(B1[i], HDIM, "b1_" + Suffix);
            LoadWeights(B2[i], YDIM, "b2_" + Suffix);            
        }
    }       
}

FString UNeuralNetwork::GetSuffix(int& Value)
{
    FString Number = FString::FromInt(Value);
    if (Value < 10)
        return "00" + Number + ".bin";
    if (Value < 100)
        return "0" + Number + ".bin";
    return Number + ".bin";
}

void UNeuralNetwork::Predict()
{
    //float PAmount;
    //int PIndex0, , PIndex2, PIndex3;
    int PIndex1;

    Xp = (Xp - Xmean) / Xstd;

    switch (Mode)
    {
    case MODE_CONSTANT:
    case MODE_LINEAR:
    case MODE_CUBIC:
        PIndex1 = FMath::Clamp((int)(Phase / ( 2 * PI ) * 50), 0, 49);
        //PIndex1 = (int)(Phase / (2 * PI) * 50);

        H0 = (W0[PIndex1].matrix() * Xp.matrix()).array() + B0[PIndex1];
        FEigenHelper::ELU(H0);
        H1 = (W1[PIndex1].matrix() * H0.matrix()).array() + B1[PIndex1];
        FEigenHelper::ELU(H1);
        Yp = (W2[PIndex1].matrix() * H1.matrix()).array() + B2[PIndex1];
        break;
    default: break;
    }

    Yp = ( Yp * Ystd ) + Ymean;

}

void UNeuralNetwork::UpdateNetworkInput(UTrajectoryComponent* TrajectoryComponent, const TArray<FJointTransform>& Joints, FVector RootVelocity, FVector RootAccel)
{
    TArray<FTrajectoryPoint>& Trajectories = TrajectoryComponent->GetTrajectoryPoints();
    const TArray<FMovementStyle>& MovementStyles = TrajectoryComponent->GetMovementStyles();
    const int TrajectoryLength = Trajectories.Num();
    const int RootPoint = TrajectoryLength / 2;
    const int W = TrajectoryLength / 10;
    
    FVector RootLocation = FVector(
        Trajectories[RootPoint].Location.X,
        Trajectories[RootPoint].Location.Y,
        Trajectories[RootPoint].Height
    );

    FQuat RootRotation = Trajectories[RootPoint].Rotation;
    
    //Input Trajectory Positions / Directions
    for (int i = 0; i < TrajectoryLength; i+=10) {        
        FVector Location = RootRotation.Inverse() * (Trajectories[i].Location - RootLocation);
        FVector Direction = RootRotation.Inverse() * Trajectories[i].Direction;  
        Xp((W*0)+i/10) = Location.Y;
        Xp((W*1)+i/10) = Location.X;
        Xp((W*2)+i/10) = Direction.Y;
        Xp((W*3)+i/10) = Direction.X;
    }
    
    //Input Trajectory Gaits
    for (int i = 0; i < TrajectoryLength; i+=10) {        
        Xp((W*4)+i/10) = MovementStyles[i].Values[(int)EMovementType::Stand];
        Xp((W*5)+i/10) = MovementStyles[i].Values[(int)EMovementType::Walk];
        Xp((W*6)+i/10) = MovementStyles[i].Values[(int)EMovementType::Jog];
        Xp((W*7)+i/10) = MovementStyles[i].Values[(int)EMovementType::Crouch];
        Xp((W*8)+i/10) = MovementStyles[i].Values[(int)EMovementType::Jump];
        Xp((W*9)+i/10) = 0.0;
    }

    const FVector PreviousRootLocation = FVector(
        Trajectories[RootPoint-1].Location.X, 
        Trajectories[RootPoint-1].Location.Y,
        Trajectories[RootPoint-1].Height
    );
    const FQuat PreviousRootRotation = Trajectories[RootPoint-1].Rotation;
    const int JoinNumber = 68;

    int InputPosition = W*10;  
    for (int i = 0; i < JoinNumber; i++) {        
        FVector Location = PreviousRootRotation.Inverse() * (Joints[i].Location - PreviousRootLocation);
        FVector PreviousLocation = PreviousRootRotation.Inverse()*Joints[i].Velocity;
        Xp(InputPosition+(JoinNumber*3*0)+(i*3+0)) = Location.Y;
        Xp(InputPosition+(JoinNumber*3*0)+(i*3+1)) = Location.Z;
        Xp(InputPosition+(JoinNumber*3*0)+(i*3+2)) = Location.X;
        Xp(InputPosition+(JoinNumber*3*1)+(i*3+0)) = PreviousLocation.Y;
        Xp(InputPosition+(JoinNumber*3*1)+(i*3+1)) = PreviousLocation.Z;
        Xp(InputPosition+(JoinNumber*3*1)+(i*3+2)) = PreviousLocation.X;
    }
    InputPosition += (JoinNumber * 3 * 2);
    //// Root Velocity X Y
    Xp(InputPosition + 0) = -RootVelocity.Y;
    Xp(InputPosition + 1) = RootVelocity.X;
    //// Root acceleration
    Xp(InputPosition + 2) = -RootAccel.Y;
    Xp(InputPosition + 3) = RootAccel.Z;
    Xp(InputPosition + 4) = RootAccel.X;

    //// Trajectory heights
    InputPosition += 5;

    const float SidePointsOffset = 0.0f;
    
    for (int i = 0; i < TrajectoryLength; i += 10) {
        FVector LocationRight = Trajectories[i].Location + (Trajectories[i].Rotation * FVector(0.0f, SidePointsOffset, 0.0f));
        FVector LocationLeft  = Trajectories[i].Location + (Trajectories[i].Rotation * FVector(0.0f, -SidePointsOffset, 0.0f));

        Xp[InputPosition + (W * 0) + (i / 10)] = TrajectoryComponent->GetHeightSample(LocationRight) - RootLocation.Z;
        Xp[InputPosition + (W * 1) + (i / 10)] = Trajectories[i].Location.Z - RootLocation.Z;
        Xp[InputPosition + (W * 2) + (i / 10)] = TrajectoryComponent->GetHeightSample(LocationLeft) - RootLocation.Z;
    }
}

