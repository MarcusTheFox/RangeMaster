// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeMaster/Public/Instance/InstanceSubsystem/SettingsManagerSubsystem.h"

#include "Data/SettingsAssetData.h"
#include "Instance/RangeMasterGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USettingsManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
    
	LoadAssets();
	LoadSettings();
	ApplyAllSettings();
}

void USettingsManagerSubsystem::ApplyAllSettings()
{
	ApplyAudioSettings();
	ApplyControlsSettings();
}

void USettingsManagerSubsystem::LoadAssets()
{
	URangeMasterGameInstance* GameInstance = Cast<URangeMasterGameInstance>(GetGameInstance());
	if (!GameInstance || !GameInstance->SettingsAssetData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsAssetData is not set in GameInstance!"));
		return;
	}

	USettingsAssetData* LoadedAssets = GameInstance->SettingsAssetData.LoadSynchronous();
	if (!LoadedAssets)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load SettingsDataAsset."));
		return;
	}

	SettingsSoundMix = LoadedAssets->SettingsSoundMix.LoadSynchronous();
	MasterSoundClass = LoadedAssets->MasterSoundClass.LoadSynchronous();
	MusicSoundClass = LoadedAssets->MusicSoundClass.LoadSynchronous();
	SFXSoundClass = LoadedAssets->SFXSoundClass.LoadSynchronous();
}

void USettingsManagerSubsystem::LoadSettings()
{
	SaveSettingsObject = Cast<URangeMasterSaveSettings>(
		UGameplayStatics::LoadGameFromSlot(URangeMasterSaveSettings::SaveSlotName, 0));

	if (!SaveSettingsObject)
	{
		SaveSettingsObject = Cast<URangeMasterSaveSettings>(
			UGameplayStatics::CreateSaveGameObject(URangeMasterSaveSettings::StaticClass()));
	}

	CurrentAudioSettings = SaveSettingsObject->AudioSettings;
	CurrentControlsSettings = SaveSettingsObject->ControlsSettings;
}

void USettingsManagerSubsystem::ApplyAudioSettings()
{
	if (!GetWorld() || !SettingsSoundMix || !MasterSoundClass || !MusicSoundClass || !SFXSoundClass)
	{
        UE_LOG(LogTemp, Error, TEXT("Cannot apply audio settings, asset references are not loaded!"));
		return;
	}
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SettingsSoundMix);
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SettingsSoundMix, MasterSoundClass,
	                                           CurrentAudioSettings.MasterVolume, 1.0f, 0.0f);
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SettingsSoundMix, MusicSoundClass,
	                                           CurrentAudioSettings.MusicVolume, 1.0f, 0.0f);
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SettingsSoundMix, SFXSoundClass,
	                                           CurrentAudioSettings.SFXVolume, 1.0f, 0.0f);
}

void USettingsManagerSubsystem::ApplyControlsSettings()
{
}

void USettingsManagerSubsystem::SaveSettings()
{
	if (!SaveSettingsObject) return;

	SaveSettingsObject->AudioSettings = CurrentAudioSettings;
	SaveSettingsObject->ControlsSettings = CurrentControlsSettings;

	UGameplayStatics::SaveGameToSlot(SaveSettingsObject, URangeMasterSaveSettings::SaveSlotName, 0);
}

void USettingsManagerSubsystem::SetGameAudioSettings(FGameAudioSettings AudioSettings)
{
	if (!SaveSettingsObject) return;

	CurrentAudioSettings = AudioSettings;
	ApplyAudioSettings();
	SaveSettings();
}

void USettingsManagerSubsystem::SetGameControlsSettings(FGameControlsSettings ControlsSettings)
{
	if (!SaveSettingsObject) return;

	CurrentControlsSettings = ControlsSettings;
	ApplyControlsSettings();
	SaveSettings();
}

void USettingsManagerSubsystem::SetMasterVolume(float Value)
{
	CurrentAudioSettings.MasterVolume = FMath::Clamp(Value, 0.0f, 1.0f);
	ApplyAudioSettings();
	SaveSettings();
}

void USettingsManagerSubsystem::SetMusicVolume(float Value)
{
	CurrentAudioSettings.MusicVolume = FMath::Clamp(Value, 0.0f, 1.0f);
	ApplyAudioSettings();
	SaveSettings();
}

void USettingsManagerSubsystem::SetSFXVolume(float Value)
{
	CurrentAudioSettings.SFXVolume = FMath::Clamp(Value, 0.0f, 1.0f);
	ApplyAudioSettings();
	SaveSettings();
}

void USettingsManagerSubsystem::SetMouseSensitivity(float Value)
{
	CurrentControlsSettings.MouseSensitivity = FMath::Max(0.0f, Value);
	ApplyControlsSettings();
	SaveSettings();
}