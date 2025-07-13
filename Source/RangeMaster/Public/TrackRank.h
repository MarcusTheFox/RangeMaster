// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrackRank.generated.h"

UENUM(BlueprintType)
enum class ETrackRank : uint8
{
	SS			UMETA(DisplayName = "SS"),
	S			UMETA(DisplayName = "S"),
	A			UMETA(DisplayName = "A"),
	B			UMETA(DisplayName = "B"),
	C			UMETA(DisplayName = "C"),
	D			UMETA(DisplayName = "D"),
	E			UMETA(DisplayName = "E"),
	None		UMETA(DisplayName = "None")
}; 