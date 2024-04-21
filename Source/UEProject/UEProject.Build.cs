// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEProject : ModuleRules
{
	public UEProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","UMG", "EnhancedInput"});
		
		PublicIncludePaths.AddRange(
        	new string[] {
            "UEProject",
            "UEProject/Interface",
			"UEProject/Actor",
			"UEProject/GameMode",
			"UEProject/PlayerController",
			"UEProject/Compo",
			"UEProject/Struct",
			"UEProject/UI",
			"UEProject/Animation",
			"UEProject/AI",
        });
	}
}
