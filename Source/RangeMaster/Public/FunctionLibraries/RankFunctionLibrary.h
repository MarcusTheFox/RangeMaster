// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enums/Judgement.h"
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
	static FText GetJudgementText(EJudgement Judgement);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearColor GetJudgementColor(EJudgement Judgement);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ETrackRank CalculateTrackRank(const int32 Score, const int32 MaxScore);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 CalculateMaxScore(const int32 TargetCount);
};
