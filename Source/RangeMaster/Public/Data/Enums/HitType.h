// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitType.generated.h"

UENUM(BlueprintType)
enum class EHitType : uint8
{
	Perfect		UMETA(DisplayName = "Perfect"),
	Miss		UMETA(DisplayName = "Miss"),
	Lost		UMETA(DisplayName = "Lost")
}; 