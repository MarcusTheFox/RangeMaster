// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrackRank.h"
#include "TrackSaveData.generated.h"

USTRUCT(BlueprintType)
struct FTrackSaveData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETrackRank MaxRank = ETrackRank::None;

	FTrackSaveData()
		: MaxScore(0), MaxRank(ETrackRank::None)
	{}
}; 