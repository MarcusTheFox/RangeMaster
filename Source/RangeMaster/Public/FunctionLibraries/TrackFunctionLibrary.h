﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/BeatMapData.h"
#include "Data/Structs/BeatMapTypes.h"
#include "Data/Structs/TrackInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundWaveProcedural.h"
#include "TrackFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UTrackFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Track Management")
	static TArray<FTrackInfo> LoadAllTracksMetadata(const FString& Directory);
	
	UFUNCTION(BlueprintCallable, Category = "Track Management")
	static bool LoadBeatMapForTrack(const FTrackInfo& Track, const FString& TracksDirectory,
		TArray<FBeatMapData>& OutBeatMap, FBeatMapSettings& OutSettings);
	
	UFUNCTION(BlueprintCallable, Category = "Track Management")
	static USoundWaveProcedural* CreateProceduralSoundWave(const FString& FilePath);
	
	UFUNCTION(BlueprintCallable, Category = "Track Management|Metadata")
	static float GetWavDurationSeconds(const FString& FilePath);
	
	UFUNCTION(BlueprintCallable, Category = "Track Management|Metadata")
	static int32 GetBeatMapTargetCount(const FString& FilePath);
	
	UFUNCTION(BlueprintCallable, Category = "Track Management")
	static bool GetBeatMapFromTrackInfo(const FTrackInfo& TrackInfo, TArray<FBeatMapData>& OutBeatMap,
		FBeatMapSettings& OutSettings);

	UFUNCTION(BlueprintCallable, Category = "Track Management")
	static bool GetSoundWaveFromTrackInfo(FTrackInfo TrackInfo, USoundWave*& OutSoundWave);

private:
	static bool LoadAndParseWavInfo(const FString& FilePath, TArray<uint8>& OutRawData, FWaveModInfo& OutWaveInfo);
	static float CalculateDurationFromWavInfo(const FWaveModInfo& WaveInfo);
};