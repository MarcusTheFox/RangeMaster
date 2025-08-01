// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SettingsAssetData.h"
#include "Engine/GameInstance.h"
#include "RangeMasterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API URangeMasterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<USettingsAssetData> SettingsAssetData;
};
