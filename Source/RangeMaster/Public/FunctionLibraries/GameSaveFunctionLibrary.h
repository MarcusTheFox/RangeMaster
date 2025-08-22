// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/TrackSaveData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameSaveFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UGameSaveFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SaveTrackResult(FName TrackID, int32 Score, ETrackRank Rank);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetTrackResult(FName TrackID, FTrackSaveData& OutResult);

	UFUNCTION(BlueprintCallable)
	static bool DeleteTrackResult(const FName TrackID);
};
