// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enums/Judgement.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CompressionFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RANGEMASTER_API UCompressionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TArray<uint8> PackJudgements(const TArray<EJudgement>& Judgements);
	static TArray<EJudgement> UnpackJudgements(const TArray<uint8>& Judgements, int32 TotalJudgements);
};
