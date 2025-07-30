// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BeatMapData.h"
#include "Data/TimeMapData.h"
#include "Data/TrackDataRow.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeatMapFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UBeatMapFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static TArray<T> GetDataFromDataTable(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FTrackDataRow> GetTrackData(UDataTable* TrackDataTable);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FBeatMapData> GetBeatMapData(UDataTable* BeatMapTable);

	static TArray<FTimeMapData> GetTimeMapData(UDataTable* BeatMapTable);
	
	static TArray<FTimeMapData> ConvertBeatMapToBeatTimes(TArray<FBeatMapData> BeatMapData);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetBeatMapDuration(UDataTable* BeatMapTable);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetTotalTargetCount(UDataTable* BeatMapTable);
};
