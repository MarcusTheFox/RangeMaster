// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/RangeMasterSaveSettings.h"
#include "Data/Structs/SettingsData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SettingsManagerSubsystem.generated.h"

class USettingsAssetData;
/**
 * 
 */
UCLASS()
class RANGEMASTER_API USettingsManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USettingsManagerSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ConfigureSubsystem(USettingsAssetData* InSettingsAssetData);
	
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetGameAudioSettings(FGameAudioSettings AudioSettings);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetGameControlsSettings(FGameControlsSettings ControlsSettings);
    
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMasterVolume(float Value);
    
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMusicVolume(float Value);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSFXVolume(float Value);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetUIVolume(float Value);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMouseSensitivity(float Value);

	UFUNCTION(BlueprintPure, Category = "Settings")
	const FGameAudioSettings& GetAudioSettings() const { return CurrentAudioSettings; }
    
	UFUNCTION(BlueprintPure, Category = "Settings")
	const FGameControlsSettings& GetControlsSettings() const { return CurrentControlsSettings; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<USettingsAssetData> SettingsAssets;

private:
	void LoadAssets();
	void LoadSettings();
	void ApplyAllSettings();
	void ApplyAudioSettings();
	void ApplyControlsSettings();
	
	FGameAudioSettings CurrentAudioSettings;
	FGameControlsSettings CurrentControlsSettings;
	
	UPROPERTY()
	TObjectPtr<URangeMasterSaveSettings> SaveSettingsObject;
	
	UPROPERTY(Transient)
	TObjectPtr<USoundMix> SettingsSoundMix;
	UPROPERTY(Transient)
	TObjectPtr<USoundClass> MasterSoundClass;
	UPROPERTY(Transient)
	TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY(Transient)
	TObjectPtr<USoundClass> SFXSoundClass;
	UPROPERTY(Transient)
	TObjectPtr<USoundClass> UISoundClass;
	UPROPERTY(Transient)
	TObjectPtr<USettingsAssetData> LoadedSettingsAssets;
};
