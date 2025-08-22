// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enums/Judgement.h"
#include "Data/Enums/TrackRank.h"
#include "TrackSaveData.generated.h"

USTRUCT(BlueprintType)
struct FTrackSaveData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETrackRank MaxRank = ETrackRank::None;

	UPROPERTY()
	int32 JudgementCount = 0;

	UPROPERTY()
	TArray<uint8> Judgements;

	FTrackSaveData() {}
}; 