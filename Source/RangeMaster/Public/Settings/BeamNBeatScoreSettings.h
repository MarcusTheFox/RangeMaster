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
	int32 BasePoints = 100;

	UPROPERTY(Config, EditAnywhere, Category = "Score")
	int32 BaseMultiplier = 1;
	
	UPROPERTY(Config, EditAnywhere, Category = "Score")
	TArray<FComboTierData> ComboTiers;

	static const UBeamNBeatScoreSettings* Get()
	{
		return GetDefault<UBeamNBeatScoreSettings>();
	}
};
