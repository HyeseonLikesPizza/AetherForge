// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AetherForge : ModuleRules
{
	public AetherForge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", 
			"EnhancedInput",
			"GameplayAbilities", // GAS
			"GameplayTags",
			"GameplayTasks",
			"NetCore",
			"UMG",
			"NavigationSystem",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		
	}
}
