// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TArray<AActor*> SortActorArrayByLabel(UPARAM(ref) TArray<AActor*>& Array, bool bAscending);
};
