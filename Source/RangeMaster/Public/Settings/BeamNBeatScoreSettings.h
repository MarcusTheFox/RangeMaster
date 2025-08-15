// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/ComboTierData.h"
#include "Engine/DeveloperSettings.h"
#include "BeamNBeatScoreSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Beam & Beat Settings - Score"))
class RANGEMASTER_API UBeamNBeatScoreSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Score")
	TArray<FComboTierData> ComboTiers;

	UPROPERTY(Config, EditAnywhere, Category = "Score")
	int32 BasePoints;

	static const UBeamNBeatScoreSettings* Get()
	{
		return GetDefault<UBeamNBeatScoreSettings>();
	}
};
