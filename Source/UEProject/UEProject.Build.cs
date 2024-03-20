// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEProject : ModuleRules
{
	public UEProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","UMG"});
		
		PublicIncludePaths.AddRange(
        	new string[] {
            "UEProject",
            "UEProject/Interface",
			"UEProject/Actor",
			"UEProject/GameMode",
			"UEProject/PlayerController",			
        });
	}
}
