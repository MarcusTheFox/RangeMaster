#pragma once

#include "CoreMinimal.h"
#include "ComboTierData.generated.h"

USTRUCT(BlueprintType)
struct FComboTierData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Tier", meta = (ClampMin = "1"))
	int32 Threshold = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Tier", meta = (ClampMin = "1"))
	int32 Multiplier = 1;
};