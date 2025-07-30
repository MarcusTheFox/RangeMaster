// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UGameUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText SecondsToTime(float Seconds);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject"))
	static class ARangeMasterGameMode* GetRangeMasterGameMode(const UObject* WorldContextObject);
};
