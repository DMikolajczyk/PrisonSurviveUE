// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PrisonSurviveUE : ModuleRules
{
	public PrisonSurviveUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks", "NavigationSystem" });
        PrivateDependencyModuleNames.AddRange(new string[] {"Slate", "SlateCore" });
    }
}
