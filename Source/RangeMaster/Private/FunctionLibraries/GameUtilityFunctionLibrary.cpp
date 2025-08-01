// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GameUtilityFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Core/RangeMasterGameMode.h"

FText UGameUtilityFunctionLibrary::SecondsToTime(float Seconds)
{
	if (Seconds < 0.0f)
	{
		Seconds = 0.0f;
	}
	
	int32 TotalSeconds = FMath::FloorToInt(Seconds);
	int32 Minutes = TotalSeconds / 60;
	int32 RemainingSeconds = TotalSeconds % 60;
	
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, RemainingSeconds);
	
	return FText::FromString(TimeString);
}

ARangeMasterGameMode* UGameUtilityFunctionLibrary::GetRangeMasterGameMode(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;
    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    return Cast<ARangeMasterGameMode>(UGameplayStatics::GetGameMode(World));
}