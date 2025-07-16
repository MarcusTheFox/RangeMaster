// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrackRank.h"
#include "HitType.h"
#include "TrackSaveData.h"
#include "SaveGame/RangeMasterSaveGame.h"
#include "Data/BeatMapData.h"
#include "GameFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText SecondsToTime(float Seconds);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetRankText(ETrackRank Rank);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetRankComment(ETrackRank Rank);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearColor GetRankColor(ETrackRank Rank);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetHitTypeText(EHitType HitType);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearColor GetHitTypeColor(EHitType HitType);
	
	UFUNCTION(BlueprintCallable)
	static void SaveTrackResult(FName TrackID, int32 Score, ETrackRank Rank);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetTrackResult(FName TrackID, FTrackSaveData& OutResult);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TArray<FBeatMapData> GetBeatMapData(UDataTable* BeatMapTable);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetBeatMapDuration(UDataTable* BeatMapTable);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetBeatMapCount(UDataTable* BeatMapTable);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject"))
	static class ARangeMasterGameMode* GetRangeMasterGameMode(const UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static ETrackRank CalculateTrackRank(const TMap<EHitType, int32>& HitTypeCounts, int32 TotalBeats);
};
