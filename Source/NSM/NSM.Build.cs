// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NSM : ModuleRules
{
	public NSM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
		bEnableExceptions = true;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AnimGraphRuntime" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "AnimGraph", "BlueprintGraph", "AnimGraphRuntime" });
	}
}
