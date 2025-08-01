// Fill out your copyright notice in the Description page of Project Settings.


#include "Instance/RangeMasterGameInstance.h"

#include "Instance/InstanceSubsystem/SettingsManagerSubsystem.h"

void URangeMasterGameInstance::Init()
{
	Super::Init();

	if (USettingsManagerSubsystem* SettingsSubsystem = GetSubsystem<USettingsManagerSubsystem>())
	{
		USettingsAssetData* LoadedAsset = SettingsAssetData.LoadSynchronous();
		SettingsSubsystem->ConfigureSubsystem(LoadedAsset);
		UE_LOG(LogTemp, Log, TEXT("SettingsManagerSubsystem configured successfully from C++."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get SettingsManagerSubsystem in URangeMasterGameInstance::Init()."));
	}
}
