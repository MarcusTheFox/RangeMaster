// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TrackSaveData.h"
#include "RangeMasterSaveGame.generated.h"

UCLASS()
class RANGEMASTER_API URangeMasterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URangeMasterSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tracks")
	FTrackSaveData TrackResult;
}; 