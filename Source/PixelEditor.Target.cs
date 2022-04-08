// © 2022, Matthew Barham. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PixelEditorTarget : TargetRules
{
	public PixelEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Pixel" } );
	}
}
