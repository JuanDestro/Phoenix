// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Animation/Skeleton.h"
#include "UObject/NoExportTypes.h"
#include "Utility/EigenHelper.h"
#include "TestPawn.generated.h"

DECLARE_STATS_GROUP(TEXT("NN"), STATGROUP_NN, STATCAT_Advanced);
DECLARE_CYCLE_STAT_EXTERN(TEXT("NNCycles"), STAT_NNCycles, STATGROUP_NN, NSM_API);

class UTrajectoryComponent;
class UNeuralNetwork;
class UCameraComponent;
class UCapsuleComponent;
class USpringArmComponent;



USTRUCT(BlueprintType)
struct FJointTransform
{
	GENERATED_BODY()

	FVector Location;
	FVector Direction;
	FQuat Rotation;
	FVector Velocity;



	FJointTransform()
		: Location(FVector::ZeroVector), Direction(FVector::ZeroVector), Rotation(FQuat::Identity), Velocity(FVector::ZeroVector)
	{
	}

	FJointTransform(FVector InLocation)
		: Location(InLocation), Direction(FVector::ZeroVector), Rotation(FQuat::Identity), Velocity(FVector::ZeroVector)
	{
	}

	
};
USTRUCT(BlueprintType)
struct FXQuery
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TArray<float> X;


};
USTRUCT(BlueprintType)
struct FYArray
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<float> Y;


};


USTRUCT(BlueprintType)
struct FStructYP
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float MemberVar_1;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_2;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_3;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_4;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_5;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_6;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_7;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_8;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_9;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_10;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_11;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_12;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_13;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_14;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_15;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_16;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_17;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_18;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_19;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_20;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_21;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_22;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_23;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_24;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_25;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_26;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_27;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_28;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_29;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_30;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_31;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_32;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_33;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_34;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_35;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_36;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_37;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_38;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_39;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_40;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_41;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_42;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_43;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_44;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_45;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_46;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_47;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_48;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_49;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_50;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_51;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_52;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_53;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_54;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_55;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_56;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_57;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_58;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_59;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_60;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_61;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_62;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_63;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_64;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_65;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_66;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_67;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_68;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_69;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_70;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_71;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_72;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_73;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_74;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_75;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_76;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_77;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_78;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_79;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_80;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_81;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_82;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_83;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_84;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_85;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_86;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_87;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_88;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_89;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_90;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_91;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_92;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_93;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_94;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_95;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_96;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_97;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_98;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_99;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_100;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_101;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_102;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_103;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_104;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_105;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_106;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_107;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_108;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_109;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_110;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_111;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_112;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_113;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_114;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_115;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_116;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_117;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_118;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_119;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_120;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_121;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_122;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_123;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_124;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_125;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_126;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_127;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_128;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_129;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_130;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_131;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_132;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_133;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_134;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_135;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_136;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_137;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_138;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_139;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_140;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_141;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_142;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_143;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_144;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_145;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_146;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_147;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_148;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_149;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_150;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_151;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_152;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_153;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_154;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_155;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_156;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_157;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_158;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_159;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_160;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_161;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_162;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_163;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_164;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_165;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_166;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_167;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_168;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_169;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_170;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_171;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_172;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_173;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_174;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_175;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_176;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_177;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_178;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_179;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_180;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_181;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_182;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_183;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_184;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_185;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_186;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_187;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_188;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_189;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_190;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_191;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_192;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_193;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_194;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_195;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_196;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_197;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_198;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_199;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_200;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_201;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_202;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_203;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_204;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_205;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_206;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_207;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_208;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_209;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_210;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_211;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_212;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_213;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_214;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_215;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_216;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_217;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_218;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_219;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_220;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_221;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_222;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_223;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_224;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_225;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_226;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_227;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_228;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_229;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_230;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_231;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_232;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_233;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_234;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_235;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_236;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_237;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_238;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_239;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_240;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_241;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_242;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_243;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_244;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_245;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_246;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_247;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_248;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_249;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_250;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_251;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_252;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_253;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_254;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_255;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_256;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_257;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_258;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_259;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_260;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_261;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_262;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_263;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_264;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_265;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_266;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_267;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_268;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_269;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_270;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_271;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_272;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_273;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_274;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_275;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_276;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_277;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_278;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_279;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_280;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_281;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_282;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_283;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_284;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_285;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_286;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_287;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_288;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_289;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_290;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_291;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_292;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_293;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_294;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_295;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_296;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_297;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_298;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_299;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_300;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_301;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_302;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_303;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_304;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_305;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_306;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_307;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_308;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_309;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_310;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_311;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_312;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_313;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_314;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_315;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_316;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_317;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_318;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_319;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_320;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_321;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_322;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_323;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_324;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_325;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_326;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_327;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_328;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_329;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_330;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_331;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_332;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_333;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_334;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_335;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_336;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_337;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_338;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_339;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_340;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_341;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_342;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_343;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_344;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_345;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_346;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_347;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_348;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_349;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_350;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_351;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_352;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_353;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_354;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_355;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_356;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_357;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_358;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_359;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_360;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_361;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_362;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_363;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_364;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_365;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_366;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_367;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_368;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_369;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_370;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_371;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_372;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_373;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_374;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_375;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_376;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_377;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_378;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_379;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_380;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_381;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_382;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_383;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_384;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_385;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_386;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_387;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_388;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_389;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_390;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_391;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_392;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_393;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_394;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_395;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_396;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_397;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_398;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_399;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_400;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_401;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_402;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_403;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_404;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_405;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_406;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_407;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_408;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_409;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_410;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_411;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_412;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_413;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_414;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_415;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_416;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_417;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_418;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_419;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_420;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_421;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_422;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_423;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_424;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_425;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_426;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_427;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_428;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_429;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_430;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_431;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_432;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_433;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_434;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_435;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_436;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_437;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_438;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_439;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_440;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_441;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_442;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_443;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_444;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_445;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_446;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_447;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_448;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_449;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_450;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_451;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_452;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_453;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_454;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_455;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_456;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_457;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_458;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_459;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_460;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_461;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_462;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_463;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_464;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_465;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_466;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_467;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_468;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_469;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_470;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_471;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_472;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_473;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_474;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_475;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_476;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_477;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_478;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_479;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_480;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_481;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_482;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_483;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_484;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_485;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_486;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_487;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_488;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_489;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_490;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_491;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_492;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_493;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_494;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_495;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_496;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_497;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_498;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_499;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_500;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_501;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_502;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_503;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_504;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_505;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_506;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_507;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_508;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_509;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_510;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_511;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_512;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_513;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_514;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_515;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_516;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_517;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_518;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_519;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_520;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_521;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_522;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_523;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_524;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_525;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_526;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_527;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_528;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_529;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_530;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_531;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_532;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_533;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_534;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_535;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_536;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_537;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_538;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_539;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_540;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_541;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_542;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_543;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_544;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_545;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_546;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_547;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_548;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_549;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_550;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_551;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_552;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_553;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_554;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_555;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_556;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_557;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_558;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_559;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_560;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_561;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_562;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_563;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_564;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_565;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_566;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_567;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_568;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_569;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_570;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_571;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_572;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_573;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_574;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_575;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_576;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_577;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_578;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_579;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_580;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_581;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_582;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_583;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_584;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_585;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_586;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_587;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_588;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_589;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_590;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_591;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_592;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_593;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_594;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_595;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_596;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_597;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_598;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_599;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_600;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_601;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_602;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_603;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_604;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_605;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_606;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_607;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_608;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_609;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_610;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_611;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_612;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_613;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_614;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_615;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_616;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_617;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_618;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_619;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_620;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_621;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_622;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_623;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_624;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_625;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_626;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_627;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_628;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_629;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_630;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_631;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_632;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_633;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_634;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_635;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_636;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_637;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_638;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_639;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_640;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_641;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_642;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_643;
	UPROPERTY(BlueprintReadWrite)
	float MemberVar_644;
};


USTRUCT(BlueprintType)
struct FXpLMM {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		float traj_side_20_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_side_40_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_side_60_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_side_20_y;
	UPROPERTY(BlueprintReadWrite)
		float traj_side_40_y;
	UPROPERTY(BlueprintReadWrite)
		float traj_side_60_y;

	UPROPERTY(BlueprintReadWrite)
		float traj_dir_20_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_dir_40_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_dir_60_x;
	UPROPERTY(BlueprintReadWrite)
		float traj_dir_20_y;
	UPROPERTY(BlueprintReadWrite)
		float traj_dir_40_y;
	UPROPERTY(BlueprintReadWrite)
		float traj_dir_60_y;

	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_right_x;
	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_right_z;
	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_right_y;
	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_left_x;
	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_left_z;
	UPROPERTY(BlueprintReadWrite)
		float loc_pos_feet_left_y;

	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_right_x;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_right_z;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_right_y;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_left_x;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_left_z;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_feet_left_y;

	UPROPERTY(BlueprintReadWrite)
		float loc_vel_pelvis_x;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_pelvis_z;
	UPROPERTY(BlueprintReadWrite)
		float loc_vel_pelvis_y;
};





UCLASS(Blueprintable)
class NSM_API ATestPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMesh = nullptr;


public:
	// Sets default values for this pawn's properties
	ATestPawn();
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	FVector LeftFootLocation;
	UPROPERTY(BlueprintReadWrite)
	FVector RightFootLocation;

	// Velocity management
	FVector RootVel;
	FVector RootAccel;
	float VelocityMultiplier = 1.f;
	void UpdateVelocityMultiplier();

	bool HasTakenIdlePosition = false;

	float AccumulatedTime = 0.0f;

	/** left foot bone relative location */
	FVector LeftFootBoneRelativeLocation;

	/** Right foot bone relative location*/
	FVector RightFootBoneRelativeLocation;

	/** Initial Skeletal Mesh position*/
	FVector InitialMeshRelativeLocation;

	UPROPERTY(EditDefaultsOnly)
	float RootMotionMultiplier;

	UPROPERTY(EditDefaultsOnly)
	bool bUseBuffer;
	
	UPROPERTY(BlueprintReadWrite)
	bool LeftFootContact = false;
	UPROPERTY(BlueprintReadWrite)
	bool RightFootContact = false;

	UPROPERTY(BlueprintReadWrite)
	float LeftFootAlpha = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float RightFootAlpha = 0.f;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UTrajectoryComponent* TrajectoryComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* CameraComponent;
	
	UPROPERTY()
	UNeuralNetwork* NeuralNetwork = nullptr;

	UPROPERTY()
	TArray<FJointTransform> Joints;

	TArray<FQuat> OriginalRotations;

	FQuat GeneralRootRotation;

	int NumberOfJoints;


	FVector BuildLocalTransforms();	

	void DrawDebugSkeleton();

	void LoadMeanStd(Vector& InVector, int Cols, FString FileName);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNetwork(FXQuery Xp);

	UPROPERTY(BlueprintReadWrite)
	FXpLMM XQuery;

	UPROPERTY(BlueprintReadWrite)
	FXQuery XInput;

	
	
	UPROPERTY(BlueprintReadWrite)
	TArray<float> Yp;

	UPROPERTY(BlueprintReadWrite)
	TArray<FStructYP> Tabla;
	UPROPERTY(BlueprintReadWrite)
	FStructYP InputYP;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FYArray> YArrayCurrent;

	UPROPERTY(BlueprintReadWrite)
	TArray<FYArray> YArrayNext;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> ArrayFeet;
	

	Vector Xmean, Xstd;
	Vector Ymean, Ystd;

	USkeletalMeshComponent* GetSkeleton() { return SkeletalMesh; }

};
