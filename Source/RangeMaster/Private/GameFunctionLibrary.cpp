// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFunctionLibrary.h"

FText UGameFunctionLibrary::SecondsToTime(float Seconds)
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

FText UGameFunctionLibrary::GetRankText(ETrackRank Rank)
{
	switch (Rank)
	{
	case ETrackRank::None:
		return FText::FromString(TEXT("-"));
	case ETrackRank::E:
		return FText::FromString(TEXT("E"));
	case ETrackRank::D:
		return FText::FromString(TEXT("D"));
	case ETrackRank::C:
		return FText::FromString(TEXT("C"));
	case ETrackRank::B:
		return FText::FromString(TEXT("B"));
	case ETrackRank::A:
		return FText::FromString(TEXT("A"));
	case ETrackRank::S:
		return FText::FromString(TEXT("S"));
	case ETrackRank::SS:
		return FText::FromString(TEXT("SS"));
	default:
		return FText::FromString(TEXT("-"));
	}
}

FText UGameFunctionLibrary::GetRankComment(ETrackRank Rank)
{
	switch (Rank)
	{
	case ETrackRank::None:
		return FText::FromString(TEXT("No Rank"));
	case ETrackRank::E:
		return FText::FromString(TEXT("Terrible"));
	case ETrackRank::D:
		return FText::FromString(TEXT("Bad"));
	case ETrackRank::C:
		return FText::FromString(TEXT("Okay"));
	case ETrackRank::B:
		return FText::FromString(TEXT("Good"));
	case ETrackRank::A:
		return FText::FromString(TEXT("Great"));
	case ETrackRank::S:
		return FText::FromString(TEXT("Amazing"));
	case ETrackRank::SS:
		return FText::FromString(TEXT("Perfect"));
	default:
		return FText::FromString(TEXT("Unknown"));
	}
}

FLinearColor UGameFunctionLibrary::GetRankColor(ETrackRank Rank)
{
	switch (Rank)
	{
	case ETrackRank::None:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый
	case ETrackRank::E:
		return FLinearColor(0.8f, 0.2f, 0.2f, 1.0f); // Красный
	case ETrackRank::D:
		return FLinearColor(0.9f, 0.4f, 0.1f, 1.0f); // Оранжевый
	case ETrackRank::C:
		return FLinearColor(0.9f, 0.9f, 0.2f, 1.0f); // Желтый
	case ETrackRank::B:
		return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f); // Зеленый
	case ETrackRank::A:
		return FLinearColor(0.2f, 0.6f, 0.9f, 1.0f); // Синий
	case ETrackRank::S:
		return FLinearColor(0.8f, 0.2f, 0.8f, 1.0f); // Фиолетовый
	case ETrackRank::SS:
		return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f); // Белый/Золотой
	default:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый по умолчанию
	}
}

FText UGameFunctionLibrary::GetHitTypeText(EHitType HitType)
{
	switch (HitType)
	{
	case EHitType::Miss:
		return FText::FromString(TEXT("Miss"));
	case EHitType::Perfect:
		return FText::FromString(TEXT("Perfect"));
	default:
		return FText::FromString(TEXT("Unknown"));
	}
}

FLinearColor UGameFunctionLibrary::GetHitTypeColor(EHitType HitType)
{
	switch (HitType)
	{
	case EHitType::Miss:
		return FLinearColor(0.8f, 0.2f, 0.2f, 1.0f); // Красный
	case EHitType::Perfect:
		return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f); // Зеленый
	default:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый по умолчанию
	}
}