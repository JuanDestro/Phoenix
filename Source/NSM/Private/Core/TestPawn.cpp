// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TestPawn.h"
#include "Core/NeuralNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Components/TrajectoryComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utility/QuatHelper.h"
#include "Utility/VectorHelper.h"
#include "Utility/AnimInstanceMotionMatching.h"
#include "Utility/IKUtilities.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Utility/BinaryFileHelper.h"

// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent")); 
	SetRootComponent(CapsuleComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritRoll = true;
	SpringArmComponent->bInheritYaw = true;	

	TrajectoryComponent = CreateDefaultSubobject<UTrajectoryComponent>(TEXT("TrajectoryComponent"));
		
	NumberOfJoints = 68;	
	RootMotionMultiplier = 1.f;
	bUseBuffer = true;
}
void ATestPawn::LoadMeanStd(Vector& InVector, int Cols, FString FileName)
{
	FString ContentPath = FPaths::ProjectContentDir();
	FString FilePath = ContentPath + "data/" + FileName;

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
// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	Yp.SetNum(644);

	for (int i = 0; i < NumberOfJoints; ++i)
	{
		Joints.Add(FJointTransform());
		OriginalRotations.Add(FQuat::Identity);
	}

	NeuralNetwork = NewObject<UNeuralNetwork>();
	if (NeuralNetwork)
	{
		NeuralNetwork->LoadModel();
	}

	TrajectoryComponent->Camera = CameraComponent;

	LoadMeanStd(Xmean, 27, "Xmean.bin");
	LoadMeanStd(Xstd, 27, "Xstd.bin");
	LoadMeanStd(Ymean, 644, "Ymean.bin");
	LoadMeanStd(Ystd, 644, "Ystd.bin");

	//FTimerHandle Timer;
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATestPawn::UpdateVelocityMultiplier, 2.f, true);
}


void ATestPawn::UpdateVelocityMultiplier()
{
	VelocityMultiplier = UKismetMathLibrary::RandomFloatInRange(0.5f, 2.f);
}



void ATestPawn::MoveForward(float Value)
{
	ATestPawn::AddMovementInput(CameraComponent->GetForwardVector(), Value);
}

void ATestPawn::MoveRight(float Value)
{
	ATestPawn::AddMovementInput(CameraComponent->GetRightVector(), Value);
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorTransform = BuildLocalTransforms();

	//This is just for testing purpose
	FVector FixedLocation = Joints[0].Location;
	//SetActorRelativeLocation(FixedLocation);
	//UE_LOG(LogTemp, Warning, TEXT("C++ Tick"))


}




// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ATestPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ATestPawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATestPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestPawn::MoveRight);	
}

DEFINE_STAT(STAT_NNCycles);
FVector ATestPawn::BuildLocalTransforms()
{
	SCOPE_CYCLE_COUNTER(STAT_NNCycles);
	
	TArray<FTrajectoryPoint> TrajectoryPoints = TrajectoryComponent->GetTrajectoryPoints();
	TArray<FMovementStyle> MovementStyles = TrajectoryComponent->GetMovementStyles();
    if (TrajectoryPoints.Num() == 0)
    {
    	return FVector(0.f);
    }
    	
    const int TrajectoryLength = TrajectoryComponent->GetTrajectoryLength(); 
    const int RootPoint = TrajectoryLength / 2;

    const float StandAmount = TrajectoryComponent->GetStandAmount();

    NeuralNetwork->UpdateNetworkInput(TrajectoryComponent, Joints, RootVel, RootAccel);
    NeuralNetwork->Predict();

	TrajectoryPoints = TrajectoryComponent->GetTrajectoryPoints();
	
	FVector RootLocation = GetActorLocation();

	FQuat RootRotation = GetActorTransform().GetRotation();
    
	
	
	float valor = InputYP.MemberVar_1;
	float valor2 = InputYP.MemberVar_2;
	float valor3 = InputYP.MemberVar_3;

	//Vector custom from Data Table YP
	Vector Q = Vector::Zero(644);
	Vector Z = Vector::Zero(644);
	if (!bUseBuffer)
	{
		Q[0] = InputYP.MemberVar_1;
		Q[1] = InputYP.MemberVar_2;
		Q[2] = InputYP.MemberVar_3;
		Q[3] = InputYP.MemberVar_4;
		Q[4] = InputYP.MemberVar_5;
		Q[5] = InputYP.MemberVar_6;
		Q[6] = InputYP.MemberVar_7;
		Q[7] = InputYP.MemberVar_8;
		Q[8] = InputYP.MemberVar_9;
		Q[9] = InputYP.MemberVar_10;
		Q[10] = InputYP.MemberVar_11;
		Q[11] = InputYP.MemberVar_12;
		Q[12] = InputYP.MemberVar_13;
		Q[13] = InputYP.MemberVar_14;
		Q[14] = InputYP.MemberVar_15;
		Q[15] = InputYP.MemberVar_16;
		Q[16] = InputYP.MemberVar_17;
		Q[17] = InputYP.MemberVar_18;
		Q[18] = InputYP.MemberVar_19;
		Q[19] = InputYP.MemberVar_20;
		Q[20] = InputYP.MemberVar_21;
		Q[21] = InputYP.MemberVar_22;
		Q[22] = InputYP.MemberVar_23;
		Q[23] = InputYP.MemberVar_24;
		Q[24] = InputYP.MemberVar_25;
		Q[25] = InputYP.MemberVar_26;
		Q[26] = InputYP.MemberVar_27;
		Q[27] = InputYP.MemberVar_28;
		Q[28] = InputYP.MemberVar_29;
		Q[29] = InputYP.MemberVar_30;
		Q[30] = InputYP.MemberVar_31;
		Q[31] = InputYP.MemberVar_32;
		Q[32] = InputYP.MemberVar_33;
		Q[33] = InputYP.MemberVar_34;
		Q[34] = InputYP.MemberVar_35;
		Q[35] = InputYP.MemberVar_36;
		Q[36] = InputYP.MemberVar_37;
		Q[37] = InputYP.MemberVar_38;
		Q[38] = InputYP.MemberVar_39;
		Q[39] = InputYP.MemberVar_40;
		Q[40] = InputYP.MemberVar_41;
		Q[41] = InputYP.MemberVar_42;
		Q[42] = InputYP.MemberVar_43;
		Q[43] = InputYP.MemberVar_44;
		Q[44] = InputYP.MemberVar_45;
		Q[45] = InputYP.MemberVar_46;
		Q[46] = InputYP.MemberVar_47;
		Q[47] = InputYP.MemberVar_48;
		Q[48] = InputYP.MemberVar_49;
		Q[49] = InputYP.MemberVar_50;
		Q[50] = InputYP.MemberVar_51;
		Q[51] = InputYP.MemberVar_52;
		Q[52] = InputYP.MemberVar_53;
		Q[53] = InputYP.MemberVar_54;
		Q[54] = InputYP.MemberVar_55;
		Q[55] = InputYP.MemberVar_56;
		Q[56] = InputYP.MemberVar_57;
		Q[57] = InputYP.MemberVar_58;
		Q[58] = InputYP.MemberVar_59;
		Q[59] = InputYP.MemberVar_60;
		Q[60] = InputYP.MemberVar_61;
		Q[61] = InputYP.MemberVar_62;
		Q[62] = InputYP.MemberVar_63;
		Q[63] = InputYP.MemberVar_64;
		Q[64] = InputYP.MemberVar_65;
		Q[65] = InputYP.MemberVar_66;
		Q[66] = InputYP.MemberVar_67;
		Q[67] = InputYP.MemberVar_68;
		Q[68] = InputYP.MemberVar_69;
		Q[69] = InputYP.MemberVar_70;
		Q[70] = InputYP.MemberVar_71;
		Q[71] = InputYP.MemberVar_72;
		Q[72] = InputYP.MemberVar_73;
		Q[73] = InputYP.MemberVar_74;
		Q[74] = InputYP.MemberVar_75;
		Q[75] = InputYP.MemberVar_76;
		Q[76] = InputYP.MemberVar_77;
		Q[77] = InputYP.MemberVar_78;
		Q[78] = InputYP.MemberVar_79;
		Q[79] = InputYP.MemberVar_80;
		Q[80] = InputYP.MemberVar_81;
		Q[81] = InputYP.MemberVar_82;
		Q[82] = InputYP.MemberVar_83;
		Q[83] = InputYP.MemberVar_84;
		Q[84] = InputYP.MemberVar_85;
		Q[85] = InputYP.MemberVar_86;
		Q[86] = InputYP.MemberVar_87;
		Q[87] = InputYP.MemberVar_88;
		Q[88] = InputYP.MemberVar_89;
		Q[89] = InputYP.MemberVar_90;
		Q[90] = InputYP.MemberVar_91;
		Q[91] = InputYP.MemberVar_92;
		Q[92] = InputYP.MemberVar_93;
		Q[93] = InputYP.MemberVar_94;
		Q[94] = InputYP.MemberVar_95;
		Q[95] = InputYP.MemberVar_96;
		Q[96] = InputYP.MemberVar_97;
		Q[97] = InputYP.MemberVar_98;
		Q[98] = InputYP.MemberVar_99;
		Q[99] = InputYP.MemberVar_100;
		Q[100] = InputYP.MemberVar_101;
		Q[101] = InputYP.MemberVar_102;
		Q[102] = InputYP.MemberVar_103;
		Q[103] = InputYP.MemberVar_104;
		Q[104] = InputYP.MemberVar_105;
		Q[105] = InputYP.MemberVar_106;
		Q[106] = InputYP.MemberVar_107;
		Q[107] = InputYP.MemberVar_108;
		Q[108] = InputYP.MemberVar_109;
		Q[109] = InputYP.MemberVar_110;
		Q[110] = InputYP.MemberVar_111;
		Q[111] = InputYP.MemberVar_112;
		Q[112] = InputYP.MemberVar_113;
		Q[113] = InputYP.MemberVar_114;
		Q[114] = InputYP.MemberVar_115;
		Q[115] = InputYP.MemberVar_116;
		Q[116] = InputYP.MemberVar_117;
		Q[117] = InputYP.MemberVar_118;
		Q[118] = InputYP.MemberVar_119;
		Q[119] = InputYP.MemberVar_120;
		Q[120] = InputYP.MemberVar_121;
		Q[121] = InputYP.MemberVar_122;
		Q[122] = InputYP.MemberVar_123;
		Q[123] = InputYP.MemberVar_124;
		Q[124] = InputYP.MemberVar_125;
		Q[125] = InputYP.MemberVar_126;
		Q[126] = InputYP.MemberVar_127;
		Q[127] = InputYP.MemberVar_128;
		Q[128] = InputYP.MemberVar_129;
		Q[129] = InputYP.MemberVar_130;
		Q[130] = InputYP.MemberVar_131;
		Q[131] = InputYP.MemberVar_132;
		Q[132] = InputYP.MemberVar_133;
		Q[133] = InputYP.MemberVar_134;
		Q[134] = InputYP.MemberVar_135;
		Q[135] = InputYP.MemberVar_136;
		Q[136] = InputYP.MemberVar_137;
		Q[137] = InputYP.MemberVar_138;
		Q[138] = InputYP.MemberVar_139;
		Q[139] = InputYP.MemberVar_140;
		Q[140] = InputYP.MemberVar_141;
		Q[141] = InputYP.MemberVar_142;
		Q[142] = InputYP.MemberVar_143;
		Q[143] = InputYP.MemberVar_144;
		Q[144] = InputYP.MemberVar_145;
		Q[145] = InputYP.MemberVar_146;
		Q[146] = InputYP.MemberVar_147;
		Q[147] = InputYP.MemberVar_148;
		Q[148] = InputYP.MemberVar_149;
		Q[149] = InputYP.MemberVar_150;
		Q[150] = InputYP.MemberVar_151;
		Q[151] = InputYP.MemberVar_152;
		Q[152] = InputYP.MemberVar_153;
		Q[153] = InputYP.MemberVar_154;
		Q[154] = InputYP.MemberVar_155;
		Q[155] = InputYP.MemberVar_156;
		Q[156] = InputYP.MemberVar_157;
		Q[157] = InputYP.MemberVar_158;
		Q[158] = InputYP.MemberVar_159;
		Q[159] = InputYP.MemberVar_160;
		Q[160] = InputYP.MemberVar_161;
		Q[161] = InputYP.MemberVar_162;
		Q[162] = InputYP.MemberVar_163;
		Q[163] = InputYP.MemberVar_164;
		Q[164] = InputYP.MemberVar_165;
		Q[165] = InputYP.MemberVar_166;
		Q[166] = InputYP.MemberVar_167;
		Q[167] = InputYP.MemberVar_168;
		Q[168] = InputYP.MemberVar_169;
		Q[169] = InputYP.MemberVar_170;
		Q[170] = InputYP.MemberVar_171;
		Q[171] = InputYP.MemberVar_172;
		Q[172] = InputYP.MemberVar_173;
		Q[173] = InputYP.MemberVar_174;
		Q[174] = InputYP.MemberVar_175;
		Q[175] = InputYP.MemberVar_176;
		Q[176] = InputYP.MemberVar_177;
		Q[177] = InputYP.MemberVar_178;
		Q[178] = InputYP.MemberVar_179;
		Q[179] = InputYP.MemberVar_180;
		Q[180] = InputYP.MemberVar_181;
		Q[181] = InputYP.MemberVar_182;
		Q[182] = InputYP.MemberVar_183;
		Q[183] = InputYP.MemberVar_184;
		Q[184] = InputYP.MemberVar_185;
		Q[185] = InputYP.MemberVar_186;
		Q[186] = InputYP.MemberVar_187;
		Q[187] = InputYP.MemberVar_188;
		Q[188] = InputYP.MemberVar_189;
		Q[189] = InputYP.MemberVar_190;
		Q[190] = InputYP.MemberVar_191;
		Q[191] = InputYP.MemberVar_192;
		Q[192] = InputYP.MemberVar_193;
		Q[193] = InputYP.MemberVar_194;
		Q[194] = InputYP.MemberVar_195;
		Q[195] = InputYP.MemberVar_196;
		Q[196] = InputYP.MemberVar_197;
		Q[197] = InputYP.MemberVar_198;
		Q[198] = InputYP.MemberVar_199;
		Q[199] = InputYP.MemberVar_200;
		Q[200] = InputYP.MemberVar_201;
		Q[201] = InputYP.MemberVar_202;
		Q[202] = InputYP.MemberVar_203;
		Q[203] = InputYP.MemberVar_204;
		Q[204] = InputYP.MemberVar_205;
		Q[205] = InputYP.MemberVar_206;
		Q[206] = InputYP.MemberVar_207;
		Q[207] = InputYP.MemberVar_208;
		Q[208] = InputYP.MemberVar_209;
		Q[209] = InputYP.MemberVar_210;
		Q[210] = InputYP.MemberVar_211;
		Q[211] = InputYP.MemberVar_212;
		Q[212] = InputYP.MemberVar_213;
		Q[213] = InputYP.MemberVar_214;
		Q[214] = InputYP.MemberVar_215;
		Q[215] = InputYP.MemberVar_216;
		Q[216] = InputYP.MemberVar_217;
		Q[217] = InputYP.MemberVar_218;
		Q[218] = InputYP.MemberVar_219;
		Q[219] = InputYP.MemberVar_220;
		Q[220] = InputYP.MemberVar_221;
		Q[221] = InputYP.MemberVar_222;
		Q[222] = InputYP.MemberVar_223;
		Q[223] = InputYP.MemberVar_224;
		Q[224] = InputYP.MemberVar_225;
		Q[225] = InputYP.MemberVar_226;
		Q[226] = InputYP.MemberVar_227;
		Q[227] = InputYP.MemberVar_228;
		Q[228] = InputYP.MemberVar_229;
		Q[229] = InputYP.MemberVar_230;
		Q[230] = InputYP.MemberVar_231;
		Q[231] = InputYP.MemberVar_232;
		Q[232] = InputYP.MemberVar_233;
		Q[233] = InputYP.MemberVar_234;
		Q[234] = InputYP.MemberVar_235;
		Q[235] = InputYP.MemberVar_236;
		Q[236] = InputYP.MemberVar_237;
		Q[237] = InputYP.MemberVar_238;
		Q[238] = InputYP.MemberVar_239;
		Q[239] = InputYP.MemberVar_240;
		Q[240] = InputYP.MemberVar_241;
		Q[241] = InputYP.MemberVar_242;
		Q[242] = InputYP.MemberVar_243;
		Q[243] = InputYP.MemberVar_244;
		Q[244] = InputYP.MemberVar_245;
		Q[245] = InputYP.MemberVar_246;
		Q[246] = InputYP.MemberVar_247;
		Q[247] = InputYP.MemberVar_248;
		Q[248] = InputYP.MemberVar_249;
		Q[249] = InputYP.MemberVar_250;
		Q[250] = InputYP.MemberVar_251;
		Q[251] = InputYP.MemberVar_252;
		Q[252] = InputYP.MemberVar_253;
		Q[253] = InputYP.MemberVar_254;
		Q[254] = InputYP.MemberVar_255;
		Q[255] = InputYP.MemberVar_256;
		Q[256] = InputYP.MemberVar_257;
		Q[257] = InputYP.MemberVar_258;
		Q[258] = InputYP.MemberVar_259;
		Q[259] = InputYP.MemberVar_260;
		Q[260] = InputYP.MemberVar_261;
		Q[261] = InputYP.MemberVar_262;
		Q[262] = InputYP.MemberVar_263;
		Q[263] = InputYP.MemberVar_264;
		Q[264] = InputYP.MemberVar_265;
		Q[265] = InputYP.MemberVar_266;
		Q[266] = InputYP.MemberVar_267;
		Q[267] = InputYP.MemberVar_268;
		Q[268] = InputYP.MemberVar_269;
		Q[269] = InputYP.MemberVar_270;
		Q[270] = InputYP.MemberVar_271;
		Q[271] = InputYP.MemberVar_272;
		Q[272] = InputYP.MemberVar_273;
		Q[273] = InputYP.MemberVar_274;
		Q[274] = InputYP.MemberVar_275;
		Q[275] = InputYP.MemberVar_276;
		Q[276] = InputYP.MemberVar_277;
		Q[277] = InputYP.MemberVar_278;
		Q[278] = InputYP.MemberVar_279;
		Q[279] = InputYP.MemberVar_280;
		Q[280] = InputYP.MemberVar_281;
		Q[281] = InputYP.MemberVar_282;
		Q[282] = InputYP.MemberVar_283;
		Q[283] = InputYP.MemberVar_284;
		Q[284] = InputYP.MemberVar_285;
		Q[285] = InputYP.MemberVar_286;
		Q[286] = InputYP.MemberVar_287;
		Q[287] = InputYP.MemberVar_288;
		Q[288] = InputYP.MemberVar_289;
		Q[289] = InputYP.MemberVar_290;
		Q[290] = InputYP.MemberVar_291;
		Q[291] = InputYP.MemberVar_292;
		Q[292] = InputYP.MemberVar_293;
		Q[293] = InputYP.MemberVar_294;
		Q[294] = InputYP.MemberVar_295;
		Q[295] = InputYP.MemberVar_296;
		Q[296] = InputYP.MemberVar_297;
		Q[297] = InputYP.MemberVar_298;
		Q[298] = InputYP.MemberVar_299;
		Q[299] = InputYP.MemberVar_300;
		Q[300] = InputYP.MemberVar_301;
		Q[301] = InputYP.MemberVar_302;
		Q[302] = InputYP.MemberVar_303;
		Q[303] = InputYP.MemberVar_304;
		Q[304] = InputYP.MemberVar_305;
		Q[305] = InputYP.MemberVar_306;
		Q[306] = InputYP.MemberVar_307;
		Q[307] = InputYP.MemberVar_308;
		Q[308] = InputYP.MemberVar_309;
		Q[309] = InputYP.MemberVar_310;
		Q[310] = InputYP.MemberVar_311;
		Q[311] = InputYP.MemberVar_312;
		Q[312] = InputYP.MemberVar_313;
		Q[313] = InputYP.MemberVar_314;
		Q[314] = InputYP.MemberVar_315;
		Q[315] = InputYP.MemberVar_316;
		Q[316] = InputYP.MemberVar_317;
		Q[317] = InputYP.MemberVar_318;
		Q[318] = InputYP.MemberVar_319;
		Q[319] = InputYP.MemberVar_320;
		Q[320] = InputYP.MemberVar_321;
		Q[321] = InputYP.MemberVar_322;
		Q[322] = InputYP.MemberVar_323;
		Q[323] = InputYP.MemberVar_324;
		Q[324] = InputYP.MemberVar_325;
		Q[325] = InputYP.MemberVar_326;
		Q[326] = InputYP.MemberVar_327;
		Q[327] = InputYP.MemberVar_328;
		Q[328] = InputYP.MemberVar_329;
		Q[329] = InputYP.MemberVar_330;
		Q[330] = InputYP.MemberVar_331;
		Q[331] = InputYP.MemberVar_332;
		Q[332] = InputYP.MemberVar_333;
		Q[333] = InputYP.MemberVar_334;
		Q[334] = InputYP.MemberVar_335;
		Q[335] = InputYP.MemberVar_336;
		Q[336] = InputYP.MemberVar_337;
		Q[337] = InputYP.MemberVar_338;
		Q[338] = InputYP.MemberVar_339;
		Q[339] = InputYP.MemberVar_340;
		Q[340] = InputYP.MemberVar_341;
		Q[341] = InputYP.MemberVar_342;
		Q[342] = InputYP.MemberVar_343;
		Q[343] = InputYP.MemberVar_344;
		Q[344] = InputYP.MemberVar_345;
		Q[345] = InputYP.MemberVar_346;
		Q[346] = InputYP.MemberVar_347;
		Q[347] = InputYP.MemberVar_348;
		Q[348] = InputYP.MemberVar_349;
		Q[349] = InputYP.MemberVar_350;
		Q[350] = InputYP.MemberVar_351;
		Q[351] = InputYP.MemberVar_352;
		Q[352] = InputYP.MemberVar_353;
		Q[353] = InputYP.MemberVar_354;
		Q[354] = InputYP.MemberVar_355;
		Q[355] = InputYP.MemberVar_356;
		Q[356] = InputYP.MemberVar_357;
		Q[357] = InputYP.MemberVar_358;
		Q[358] = InputYP.MemberVar_359;
		Q[359] = InputYP.MemberVar_360;
		Q[360] = InputYP.MemberVar_361;
		Q[361] = InputYP.MemberVar_362;
		Q[362] = InputYP.MemberVar_363;
		Q[363] = InputYP.MemberVar_364;
		Q[364] = InputYP.MemberVar_365;
		Q[365] = InputYP.MemberVar_366;
		Q[366] = InputYP.MemberVar_367;
		Q[367] = InputYP.MemberVar_368;
		Q[368] = InputYP.MemberVar_369;
		Q[369] = InputYP.MemberVar_370;
		Q[370] = InputYP.MemberVar_371;
		Q[371] = InputYP.MemberVar_372;
		Q[372] = InputYP.MemberVar_373;
		Q[373] = InputYP.MemberVar_374;
		Q[374] = InputYP.MemberVar_375;
		Q[375] = InputYP.MemberVar_376;
		Q[376] = InputYP.MemberVar_377;
		Q[377] = InputYP.MemberVar_378;
		Q[378] = InputYP.MemberVar_379;
		Q[379] = InputYP.MemberVar_380;
		Q[380] = InputYP.MemberVar_381;
		Q[381] = InputYP.MemberVar_382;
		Q[382] = InputYP.MemberVar_383;
		Q[383] = InputYP.MemberVar_384;
		Q[384] = InputYP.MemberVar_385;
		Q[385] = InputYP.MemberVar_386;
		Q[386] = InputYP.MemberVar_387;
		Q[387] = InputYP.MemberVar_388;
		Q[388] = InputYP.MemberVar_389;
		Q[389] = InputYP.MemberVar_390;
		Q[390] = InputYP.MemberVar_391;
		Q[391] = InputYP.MemberVar_392;
		Q[392] = InputYP.MemberVar_393;
		Q[393] = InputYP.MemberVar_394;
		Q[394] = InputYP.MemberVar_395;
		Q[395] = InputYP.MemberVar_396;
		Q[396] = InputYP.MemberVar_397;
		Q[397] = InputYP.MemberVar_398;
		Q[398] = InputYP.MemberVar_399;
		Q[399] = InputYP.MemberVar_400;
		Q[400] = InputYP.MemberVar_401;
		Q[401] = InputYP.MemberVar_402;
		Q[402] = InputYP.MemberVar_403;
		Q[403] = InputYP.MemberVar_404;
		Q[404] = InputYP.MemberVar_405;
		Q[405] = InputYP.MemberVar_406;
		Q[406] = InputYP.MemberVar_407;
		Q[407] = InputYP.MemberVar_408;
		Q[408] = InputYP.MemberVar_409;
		Q[409] = InputYP.MemberVar_410;
		Q[410] = InputYP.MemberVar_411;
		Q[411] = InputYP.MemberVar_412;
		Q[412] = InputYP.MemberVar_413;
		Q[413] = InputYP.MemberVar_414;
		Q[414] = InputYP.MemberVar_415;
		Q[415] = InputYP.MemberVar_416;
		Q[416] = InputYP.MemberVar_417;
		Q[417] = InputYP.MemberVar_418;
		Q[418] = InputYP.MemberVar_419;
		Q[419] = InputYP.MemberVar_420;
		Q[420] = InputYP.MemberVar_421;
		Q[421] = InputYP.MemberVar_422;
		Q[422] = InputYP.MemberVar_423;
		Q[423] = InputYP.MemberVar_424;
		Q[424] = InputYP.MemberVar_425;
		Q[425] = InputYP.MemberVar_426;
		Q[426] = InputYP.MemberVar_427;
		Q[427] = InputYP.MemberVar_428;
		Q[428] = InputYP.MemberVar_429;
		Q[429] = InputYP.MemberVar_430;
		Q[430] = InputYP.MemberVar_431;
		Q[431] = InputYP.MemberVar_432;
		Q[432] = InputYP.MemberVar_433;
		Q[433] = InputYP.MemberVar_434;
		Q[434] = InputYP.MemberVar_435;
		Q[435] = InputYP.MemberVar_436;
		Q[436] = InputYP.MemberVar_437;
		Q[437] = InputYP.MemberVar_438;
		Q[438] = InputYP.MemberVar_439;
		Q[439] = InputYP.MemberVar_440;
		Q[440] = InputYP.MemberVar_441;
		Q[441] = InputYP.MemberVar_442;
		Q[442] = InputYP.MemberVar_443;
		Q[443] = InputYP.MemberVar_444;
		Q[444] = InputYP.MemberVar_445;
		Q[445] = InputYP.MemberVar_446;
		Q[446] = InputYP.MemberVar_447;
		Q[447] = InputYP.MemberVar_448;
		Q[448] = InputYP.MemberVar_449;
		Q[449] = InputYP.MemberVar_450;
		Q[450] = InputYP.MemberVar_451;
		Q[451] = InputYP.MemberVar_452;
		Q[452] = InputYP.MemberVar_453;
		Q[453] = InputYP.MemberVar_454;
		Q[454] = InputYP.MemberVar_455;
		Q[455] = InputYP.MemberVar_456;
		Q[456] = InputYP.MemberVar_457;
		Q[457] = InputYP.MemberVar_458;
		Q[458] = InputYP.MemberVar_459;
		Q[459] = InputYP.MemberVar_460;
		Q[460] = InputYP.MemberVar_461;
		Q[461] = InputYP.MemberVar_462;
		Q[462] = InputYP.MemberVar_463;
		Q[463] = InputYP.MemberVar_464;
		Q[464] = InputYP.MemberVar_465;
		Q[465] = InputYP.MemberVar_466;
		Q[466] = InputYP.MemberVar_467;
		Q[467] = InputYP.MemberVar_468;
		Q[468] = InputYP.MemberVar_469;
		Q[469] = InputYP.MemberVar_470;
		Q[470] = InputYP.MemberVar_471;
		Q[471] = InputYP.MemberVar_472;
		Q[472] = InputYP.MemberVar_473;
		Q[473] = InputYP.MemberVar_474;
		Q[474] = InputYP.MemberVar_475;
		Q[475] = InputYP.MemberVar_476;
		Q[476] = InputYP.MemberVar_477;
		Q[477] = InputYP.MemberVar_478;
		Q[478] = InputYP.MemberVar_479;
		Q[479] = InputYP.MemberVar_480;
		Q[480] = InputYP.MemberVar_481;
		Q[481] = InputYP.MemberVar_482;
		Q[482] = InputYP.MemberVar_483;
		Q[483] = InputYP.MemberVar_484;
		Q[484] = InputYP.MemberVar_485;
		Q[485] = InputYP.MemberVar_486;
		Q[486] = InputYP.MemberVar_487;
		Q[487] = InputYP.MemberVar_488;
		Q[488] = InputYP.MemberVar_489;
		Q[489] = InputYP.MemberVar_490;
		Q[490] = InputYP.MemberVar_491;
		Q[491] = InputYP.MemberVar_492;
		Q[492] = InputYP.MemberVar_493;
		Q[493] = InputYP.MemberVar_494;
		Q[494] = InputYP.MemberVar_495;
		Q[495] = InputYP.MemberVar_496;
		Q[496] = InputYP.MemberVar_497;
		Q[497] = InputYP.MemberVar_498;
		Q[498] = InputYP.MemberVar_499;
		Q[499] = InputYP.MemberVar_500;
		Q[500] = InputYP.MemberVar_501;
		Q[501] = InputYP.MemberVar_502;
		Q[502] = InputYP.MemberVar_503;
		Q[503] = InputYP.MemberVar_504;
		Q[504] = InputYP.MemberVar_505;
		Q[505] = InputYP.MemberVar_506;
		Q[506] = InputYP.MemberVar_507;
		Q[507] = InputYP.MemberVar_508;
		Q[508] = InputYP.MemberVar_509;
		Q[509] = InputYP.MemberVar_510;
		Q[510] = InputYP.MemberVar_511;
		Q[511] = InputYP.MemberVar_512;
		Q[512] = InputYP.MemberVar_513;
		Q[513] = InputYP.MemberVar_514;
		Q[514] = InputYP.MemberVar_515;
		Q[515] = InputYP.MemberVar_516;
		Q[516] = InputYP.MemberVar_517;
		Q[517] = InputYP.MemberVar_518;
		Q[518] = InputYP.MemberVar_519;
		Q[519] = InputYP.MemberVar_520;
		Q[520] = InputYP.MemberVar_521;
		Q[521] = InputYP.MemberVar_522;
		Q[522] = InputYP.MemberVar_523;
		Q[523] = InputYP.MemberVar_524;
		Q[524] = InputYP.MemberVar_525;
		Q[525] = InputYP.MemberVar_526;
		Q[526] = InputYP.MemberVar_527;
		Q[527] = InputYP.MemberVar_528;
		Q[528] = InputYP.MemberVar_529;
		Q[529] = InputYP.MemberVar_530;
		Q[530] = InputYP.MemberVar_531;
		Q[531] = InputYP.MemberVar_532;
		Q[532] = InputYP.MemberVar_533;
		Q[533] = InputYP.MemberVar_534;
		Q[534] = InputYP.MemberVar_535;
		Q[535] = InputYP.MemberVar_536;
		Q[536] = InputYP.MemberVar_537;
		Q[537] = InputYP.MemberVar_538;
		Q[538] = InputYP.MemberVar_539;
		Q[539] = InputYP.MemberVar_540;
		Q[540] = InputYP.MemberVar_541;
		Q[541] = InputYP.MemberVar_542;
		Q[542] = InputYP.MemberVar_543;
		Q[543] = InputYP.MemberVar_544;
		Q[544] = InputYP.MemberVar_545;
		Q[545] = InputYP.MemberVar_546;
		Q[546] = InputYP.MemberVar_547;
		Q[547] = InputYP.MemberVar_548;
		Q[548] = InputYP.MemberVar_549;
		Q[549] = InputYP.MemberVar_550;
		Q[550] = InputYP.MemberVar_551;
		Q[551] = InputYP.MemberVar_552;
		Q[552] = InputYP.MemberVar_553;
		Q[553] = InputYP.MemberVar_554;
		Q[554] = InputYP.MemberVar_555;
		Q[555] = InputYP.MemberVar_556;
		Q[556] = InputYP.MemberVar_557;
		Q[557] = InputYP.MemberVar_558;
		Q[558] = InputYP.MemberVar_559;
		Q[559] = InputYP.MemberVar_560;
		Q[560] = InputYP.MemberVar_561;
		Q[561] = InputYP.MemberVar_562;
		Q[562] = InputYP.MemberVar_563;
		Q[563] = InputYP.MemberVar_564;
		Q[564] = InputYP.MemberVar_565;
		Q[565] = InputYP.MemberVar_566;
		Q[566] = InputYP.MemberVar_567;
		Q[567] = InputYP.MemberVar_568;
		Q[568] = InputYP.MemberVar_569;
		Q[569] = InputYP.MemberVar_570;
		Q[570] = InputYP.MemberVar_571;
		Q[571] = InputYP.MemberVar_572;
		Q[572] = InputYP.MemberVar_573;
		Q[573] = InputYP.MemberVar_574;
		Q[574] = InputYP.MemberVar_575;
		Q[575] = InputYP.MemberVar_576;
		Q[576] = InputYP.MemberVar_577;
		Q[577] = InputYP.MemberVar_578;
		Q[578] = InputYP.MemberVar_579;
		Q[579] = InputYP.MemberVar_580;
		Q[580] = InputYP.MemberVar_581;
		Q[581] = InputYP.MemberVar_582;
		Q[582] = InputYP.MemberVar_583;
		Q[583] = InputYP.MemberVar_584;
		Q[584] = InputYP.MemberVar_585;
		Q[585] = InputYP.MemberVar_586;
		Q[586] = InputYP.MemberVar_587;
		Q[587] = InputYP.MemberVar_588;
		Q[588] = InputYP.MemberVar_589;
		Q[589] = InputYP.MemberVar_590;
		Q[590] = InputYP.MemberVar_591;
		Q[591] = InputYP.MemberVar_592;
		Q[592] = InputYP.MemberVar_593;
		Q[593] = InputYP.MemberVar_594;
		Q[594] = InputYP.MemberVar_595;
		Q[595] = InputYP.MemberVar_596;
		Q[596] = InputYP.MemberVar_597;
		Q[597] = InputYP.MemberVar_598;
		Q[598] = InputYP.MemberVar_599;
		Q[599] = InputYP.MemberVar_600;
		Q[600] = InputYP.MemberVar_601;
		Q[601] = InputYP.MemberVar_602;
		Q[602] = InputYP.MemberVar_603;
		Q[603] = InputYP.MemberVar_604;
		Q[604] = InputYP.MemberVar_605;
		Q[605] = InputYP.MemberVar_606;
		Q[606] = InputYP.MemberVar_607;
		Q[607] = InputYP.MemberVar_608;
		Q[608] = InputYP.MemberVar_609;
		Q[609] = InputYP.MemberVar_610;
		Q[610] = InputYP.MemberVar_611;
		Q[611] = InputYP.MemberVar_612;
		Q[612] = InputYP.MemberVar_613;
		Q[613] = InputYP.MemberVar_614;
		Q[614] = InputYP.MemberVar_615;
		Q[615] = InputYP.MemberVar_616;
		Q[616] = InputYP.MemberVar_617;
		Q[617] = InputYP.MemberVar_618;
		Q[618] = InputYP.MemberVar_619;
		Q[619] = InputYP.MemberVar_620;
		Q[620] = InputYP.MemberVar_621;
		Q[621] = InputYP.MemberVar_622;
		Q[622] = InputYP.MemberVar_623;
		Q[623] = InputYP.MemberVar_624;
		Q[624] = InputYP.MemberVar_625;
		Q[625] = InputYP.MemberVar_626;
		Q[626] = InputYP.MemberVar_627;
		Q[627] = InputYP.MemberVar_628;
		Q[628] = InputYP.MemberVar_629;
		Q[629] = InputYP.MemberVar_630;
		Q[630] = InputYP.MemberVar_631;
		Q[631] = InputYP.MemberVar_632;
		Q[632] = InputYP.MemberVar_633;
		Q[633] = InputYP.MemberVar_634;
		Q[634] = InputYP.MemberVar_635;
		Q[635] = InputYP.MemberVar_636;
		Q[636] = InputYP.MemberVar_637;
		Q[637] = InputYP.MemberVar_638;
		Q[638] = InputYP.MemberVar_639;
		Q[639] = InputYP.MemberVar_640;
		Q[640] = InputYP.MemberVar_641;
		Q[641] = InputYP.MemberVar_642;
		Q[642] = InputYP.MemberVar_643;
		Q[643] = InputYP.MemberVar_644;
	}
	
	//Get the Xquery to LMM in the csv
	TArray<FTrajectoryPoint>& Trajectories = TrajectoryComponent->GetTrajectoryPoints();
	
	const FQuat PreviousRootRotation = Trajectories[RootPoint - 1].Rotation;

	FVector RootLocation20 = RootRotation.Inverse() * (Trajectories[80].Location - RootLocation);
	FVector RootLocation40 = RootRotation.Inverse() * (Trajectories[100].Location - RootLocation);
	FVector RootLocation60 = RootRotation.Inverse() * (Trajectories[119].Location - RootLocation);
	FVector RootDirection20 = RootRotation.Inverse() * Trajectories[80].Direction;
	FVector RootDirection40 = RootRotation.Inverse() * Trajectories[100].Direction;
	FVector RootDirection60 = RootRotation.Inverse() * Trajectories[119].Direction;

	FVector LocationRightFoot = Joints[58].Location;
	FVector LocationLeftFoot = Joints[52].Location;

	FVector VelocityRightFoot = PreviousRootRotation.Inverse() * Joints[58].Velocity;
	FVector VelocityLeftFoot = PreviousRootRotation.Inverse() * Joints[52].Velocity;

	FVector VelocityHips = PreviousRootRotation.Inverse() * Joints[1].Velocity;

	XQuery.traj_side_20_x = RootLocation20.Y;
	XQuery.traj_side_20_y = RootLocation20.X;
	XQuery.traj_side_40_x = RootLocation40.Y;
	XQuery.traj_side_40_y = RootLocation40.X;
	XQuery.traj_side_60_x = RootLocation60.Y;
	XQuery.traj_side_60_y = RootLocation60.X;

	XQuery.traj_dir_20_x = RootDirection20.Y;
	XQuery.traj_dir_20_y = RootDirection20.X;
	XQuery.traj_dir_40_x = RootDirection40.Y;
	XQuery.traj_dir_40_y = RootDirection40.X;
	XQuery.traj_dir_60_x = RootDirection60.Y;
	XQuery.traj_dir_60_y = RootDirection60.X;
	
	XQuery.loc_pos_feet_right_x = LocationRightFoot.Y;
	XQuery.loc_pos_feet_right_z = LocationRightFoot.Z;
	XQuery.loc_pos_feet_right_y = LocationRightFoot.X;
	XQuery.loc_pos_feet_left_x = LocationLeftFoot.Y;
	XQuery.loc_pos_feet_left_z = LocationLeftFoot.Z;
	XQuery.loc_pos_feet_left_y = LocationLeftFoot.X;

	XQuery.loc_vel_feet_right_x = VelocityRightFoot.Y;
	XQuery.loc_vel_feet_right_z = VelocityRightFoot.Z;
	XQuery.loc_vel_feet_right_y = VelocityRightFoot.X;
	XQuery.loc_vel_feet_left_x = VelocityLeftFoot.Y;
	XQuery.loc_vel_feet_left_z = VelocityLeftFoot.Z;
	XQuery.loc_vel_feet_left_y = VelocityLeftFoot.X;
	
	XQuery.loc_vel_pelvis_x = VelocityHips.Y;
	XQuery.loc_vel_pelvis_z = VelocityHips.Z;
	XQuery.loc_vel_pelvis_y = VelocityHips.X;

	Vector X = Vector::Zero(27);

	X[0] = -RootLocation20.Y;
	X[1] = RootLocation20.X;
	X[2] = -RootLocation40.Y;
	X[3] = RootLocation40.X;
	X[4] = -RootLocation60.Y;
	X[5] = RootLocation60.X;
	X[6] = -RootDirection20.Y;
	X[7] = RootDirection20.X;
	X[8] = -RootDirection40.Y;
	X[9] = RootDirection40.X;
	X[10] = -RootDirection60.Y;
	X[11] = RootDirection60.X;
	X[12] = -LocationRightFoot.Y;
	X[13] = LocationRightFoot.Z;
	X[14] = LocationRightFoot.X;
	X[15] = -LocationLeftFoot.Y;
	X[16] = LocationLeftFoot.Z;
	X[17] = LocationLeftFoot.X;
	X[18] = -VelocityRightFoot.Y;
	X[19] = VelocityRightFoot.Z;
	X[20] = VelocityRightFoot.X;
	X[21] = -VelocityLeftFoot.Y;
	X[22] = VelocityLeftFoot.Z;
	X[23] = VelocityLeftFoot.X;
	X[24] = -VelocityHips.Y;
	X[25] = VelocityHips.Z;
	X[26] = VelocityHips.X;

	ArrayFeet.SetNum(6);
	for (int i = 12; i < 18; i++) {
		ArrayFeet[i-12] = X[i];
	}
	//X = (X - Xmean) / Xstd;

	TArray <float> XTemp;
	XTemp.SetNum(27);
	
	for (int i = 0; i < 27; i++) {
		XTemp[i] = X[i];
	}
	//XTemp[0] = RootLocation20.Y;
	//XTemp[1] = RootLocation20.X;
	//XTemp[2] = RootLocation40.Y;
	//XTemp[3] = RootLocation40.X;
	//XTemp[4] = RootLocation60.Y;
	//XTemp[5] = RootLocation60.X;
	//XTemp[6] = RootDirection20.Y;
	//XTemp[7] = RootDirection20.X;
	//XTemp[8] = RootDirection40.Y;
	//XTemp[9] = RootDirection40.X;
	//XTemp[10] = RootDirection60.Y;
	//XTemp[11] = RootDirection60.X;
	//XTemp[12] = LocationRightFoot.Y;
	//XTemp[13] = LocationRightFoot.Z;
	//XTemp[14] = LocationRightFoot.X;
	//XTemp[15] = LocationLeftFoot.Y;
	//XTemp[16] = LocationLeftFoot.Z;
	//XTemp[17] = LocationLeftFoot.X;
	//XTemp[18] = VelocityRightFoot.Y;
	//XTemp[19] = VelocityRightFoot.Z;
	//XTemp[20] = VelocityRightFoot.X;
	//XTemp[21] = VelocityLeftFoot.Y;
	//XTemp[22] = VelocityLeftFoot.Z;
	//XTemp[23] = VelocityLeftFoot.X;
	//XTemp[24] = VelocityHips.Y;
	//XTemp[25] = VelocityHips.Z;
	//XTemp[26] = VelocityHips.X;

	
	XInput.X = XTemp;
	Vector Y = Vector::Zero(644);
	//UE_LOG(LogTemp, Warning, TEXT("Yp %d"), Yp.Num())

	UpdateNetwork(XInput);
	TArray <float> YTemp;

	if (bUseBuffer) {
		if (YArrayCurrent.Num() <= 0) {
			return GetActorLocation();
		}

		Yp = YArrayCurrent[0].Y;
		YArrayCurrent.RemoveAt(0);


		if (Yp.Num() != 644) {
			return GetActorLocation();
		}
		for (int i = 0; i < 644; i++) {
			Y[i] = Yp[i];
		}
		
		//Y = (Y * Ystd) + Ymean;
	}
	else {
		//Vector Y = NeuralNetwork->Yp;
		//Vector Y = Q;
		Y = Q;
		if (Y.size() != 644)return GetActorLocation();
	}

	for (int i = 0; i < NumberOfJoints; i++)
		{
			int LocationPosition = 8 + ((RootPoint / 10) * 4) + (NumberOfJoints * 3 * 0);
			int VelocityPosition = 8 + ((RootPoint / 10) * 4) + (NumberOfJoints * 3 * 1);
			int RotationPosition = 8 + ((RootPoint / 10) * 4) + (NumberOfJoints * 3 * 2);

			FVector Location = FVectorHelper::MakeFromLeftHanded(
					Y[LocationPosition + i * 3 + 0],
					Y[LocationPosition + i * 3 + 1],
					Y[LocationPosition + i * 3 + 2]);

			FVector Velocity = FVectorHelper::MakeFromLeftHanded(
					Y[VelocityPosition + i * 3 + 0],
					Y[VelocityPosition + i * 3 + 1],
					Y[VelocityPosition + i * 3 + 2]);

			FQuat Rotation = FQuatHelper::QuaternionExponent(
					FVectorHelper::MakeFromLeftHanded(
						Y[RotationPosition + i * 3 + 0],
						Y[RotationPosition + i * 3 + 1],
						Y[RotationPosition + i * 3 + 2]));


			Joints[i].Location = UKismetMathLibrary::VLerp(Joints[i].Location + Velocity, Location, 0.5f);
			Joints[i].Velocity = Velocity;
			Joints[i].Rotation = Rotation;

			OriginalRotations[i] =
				FQuatHelper::QuaternionExponent(
					FVector(
						Y[RotationPosition + i * 3 + 0],
						Y[RotationPosition + i * 3 + 1],
						Y[RotationPosition + i * 3 + 2]));

		}

	bool LeftFootContactBefore = LeftFootContact;
	LeftFootContact = FMath::Clamp(Y[4] * 2.5f, 0.f, 1.f) >= 0.5f;
	RightFootContact = FMath::Clamp(Y[6] * 2.5f, 0.f, 1.f) >= 0.5f;

	LeftFootAlpha = FMath::Clamp(Y[4] * 2.5f, 0.f, 1.f);
	RightFootAlpha = FMath::Clamp(Y[6] * 2.5f, 0.f, 1.f);

	UAnimInstanceMotionMatching* FPAnim = Cast<UAnimInstanceMotionMatching>(SkeletalMesh->GetAnimInstance());

	if (!FPAnim)
		return RootLocation;

	UIKUtilities::CalculateFootIK(FPAnim, RootVel, SkeletalMesh, FName("foot_l"), FName("foot_r"), SkeletalMesh->GetBoneLocation("ball_l"),
		SkeletalMesh->GetBoneLocation("ball_r"), HasTakenIdlePosition, LeftFootAlpha, RightFootAlpha, AccumulatedTime, 14.f, 14.f, 2.f, this);

	TrajectoryComponent->PostVisualisationCalculation(NeuralNetwork->Yp);
	NeuralNetwork->UpdatePhase(StandAmount);

	if (LeftFootContact != LeftFootContactBefore) {
		VelocityMultiplier = UKismetMathLibrary::RandomFloatInRange(0.1f, 2.f);
	}

	FVector NewRootVelocity = FVector(Y[1], -Y[0], 0.f) * VelocityMultiplier;
	RootAccel = NewRootVelocity - RootVel;
	RootVel = UKismetMathLibrary::VLerp(RootVel, NewRootVelocity, 0.2);

	GeneralRootRotation = FQuat::Identity;

	RootRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector(0.f, 0.f, 1.f), FMath::RadiansToDegrees(Y[2] * RootMotionMultiplier) ).Quaternion() * RootRotation;
	RootLocation += RootRotation.RotateVector(FVector(Y[1], -Y[0], 0.f)) * RootMotionMultiplier;

	SetActorLocation(RootLocation);
	SetActorRotation(RootRotation);

	return RootLocation;

	
	
}

void ATestPawn::DrawDebugSkeleton()
{
	for (int i = 0; i < NumberOfJoints; ++i)
	{
		DrawDebugSphere(GetWorld(), Joints[i].Location, 3.0f, 6, FColor::Emerald, false, -1, 0, 3);	
	}	
}

