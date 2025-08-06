#pragma once

#include "CoreMinimal.h"
#include "TrackInfo.generated.h"

USTRUCT(BlueprintType)
struct FTrackInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName TrackID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText ArtistName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BPM = 120;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString AudioFile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString BeatMapFile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 TotalTargets = 0;
};