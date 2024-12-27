// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyGame_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MyGame;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MyGame()
	{
		if (!Z_Registration_Info_UPackage__Script_MyGame.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/MyGame",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x46D33005,
				0x42C22087,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MyGame.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_MyGame.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MyGame(Z_Construct_UPackage__Script_MyGame, TEXT("/Script/MyGame"), Z_Registration_Info_UPackage__Script_MyGame, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x46D33005, 0x42C22087));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
