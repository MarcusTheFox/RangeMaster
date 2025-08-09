// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Target.h"
#include "Engine/DeveloperSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "RangeMasterProjectSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Range Master Settings"))
class RANGEMASTER_API URangeMasterProjectSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<USoundMix> SettingsSoundMix;

	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<USoundClass> MasterSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<USoundClass> MusicSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<USoundClass> SFXSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<USoundClass> UISoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Targets")
	TSubclassOf<ATarget> TargetClass;

	static const URangeMasterProjectSettings* Get()
	{
		return GetDefault<URangeMasterProjectSettings>();
	}
};
