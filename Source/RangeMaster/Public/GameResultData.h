#pragma once

#include "CoreMinimal.h"
#include "TrackRank.h"
#include "HitType.h"
#include "GameResultData.generated.h"

USTRUCT(BlueprintType)
struct FGameResultData
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadOnly)
    int32 Score = 0;

    UPROPERTY(BlueprintReadOnly)
    ETrackRank Rank = ETrackRank::None;

    UPROPERTY(BlueprintReadOnly)
    int32 MaxCombo = 0;

    UPROPERTY(BlueprintReadOnly)
    TMap<EHitType, int32> HitTypeCounts;
}; 