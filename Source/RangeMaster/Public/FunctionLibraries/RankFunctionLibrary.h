// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enums/HitType.h"
#include "Data/Enums/TrackRank.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RankFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API URankFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ETrackRank CalculateTrackRank(const TMap<EHitType, int32>& HitTypeCounts, int32 TotalBeats);
};
