// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GMTK2020 : ModuleRules
{
	public GMTK2020(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
