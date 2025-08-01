#pragma once

#include "CoreMinimal.h"
#include "SettingsData.generated.h"

USTRUCT(BlueprintType)
struct FGameAudioSettings
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings|Audio")
	float MasterVolume = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings|Audio")
	float MusicVolume = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings|Audio")
	float SFXVolume = 1.0f;
};

USTRUCT(BlueprintType)
struct FGameControlsSettings
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings|Controls")
	float MouseSensitivity = 1.0f;
};