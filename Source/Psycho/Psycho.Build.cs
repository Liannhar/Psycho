// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Psycho : ModuleRules
{
	public Psycho(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","GameplayTasks","NavigationSystem" ,"MotionWarping"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { 
			"Psycho/Public/Characters",
			"Psycho/Public/Characters/Enemies",
			"Psycho/Public/Characters/Enemies/Components",
			"Psycho/Public/Characters/Enemies/AI",
			"Psycho/Public/Characters/Enemies/AI/Services",
			"Psycho/Public/Characters/Enemies/AI/Decorators",
			"Psycho/Public/Characters/Enemies/AI/Nodes",
			"Psycho/Public/Characters/Components",
			"Psycho/Public/Weapons",
			"Psycho/Public/Weapons/DamageTypes",
			"Psycho/Public/Pills",
			"Psycho/Public/Controllers",
			"Psycho/Public/AnimNotifies",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
