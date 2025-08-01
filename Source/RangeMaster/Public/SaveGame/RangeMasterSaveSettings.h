// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsData.h"
#include "GameFramework/SaveGame.h"
#include "RangeMasterSaveSettings.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API URangeMasterSaveSettings : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameAudioSettings AudioSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameControlsSettings ControlsSettings;

	inline static const FString SaveSlotName = TEXT("Settings");
};
