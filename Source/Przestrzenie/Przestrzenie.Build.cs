// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Przestrzenie : ModuleRules
{
	public Przestrzenie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
            "GameplayAbilities","InputCore", "EnhancedInput"});
	}
}
