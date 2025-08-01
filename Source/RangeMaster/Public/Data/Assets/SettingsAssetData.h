// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Engine/DataAsset.h"
#include "SettingsAssetData.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API USettingsAssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSoftObjectPtr<USoundMix> SettingsSoundMix;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSoftObjectPtr<USoundClass> MasterSoundClass;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSoftObjectPtr<USoundClass> MusicSoundClass;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSoftObjectPtr<USoundClass> SFXSoundClass;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSoftObjectPtr<USoundClass> UISoundClass;
};
