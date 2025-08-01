#pragma once

#include "CoreMinimal.h"
#include "CountdownInfo.generated.h"

USTRUCT(BlueprintType)
struct FCountdownInfo
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadOnly)
    float TimeLeft = 0.f;

    UPROPERTY(BlueprintReadOnly)
    float TotalTime = 0.f;

    UPROPERTY(BlueprintReadOnly)
    float Progress = 0.f; // 0..1
}; 