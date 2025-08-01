// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TrackDataRow.generated.h"

USTRUCT(BlueprintType)
struct FTrackDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TrackID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ArtistName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* SoundWave = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BPM = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "100"))
	UDataTable* BeatMap = nullptr;
};