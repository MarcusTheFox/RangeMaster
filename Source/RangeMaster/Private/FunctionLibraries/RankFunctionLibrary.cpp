// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/RankFunctionLibrary.h"

FText URankFunctionLibrary::GetRankText(ETrackRank Rank)
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

FText URankFunctionLibrary::GetRankComment(ETrackRank Rank)
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

FLinearColor URankFunctionLibrary::GetRankColor(ETrackRank Rank)
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
		return FLinearColor(1.0f, 0.84f, 0.0f, 1.0f); // Золотой
	default:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый по умолчанию
	}
}

FText URankFunctionLibrary::GetHitTypeText(EHitType HitType)
{
	switch (HitType)
	{
	case EHitType::Lost:
		return FText::FromString(TEXT("Lost"));
	case EHitType::Miss:
		return FText::FromString(TEXT("Miss"));
	case EHitType::Perfect:
		return FText::FromString(TEXT("Perfect"));
	default:
		return FText::FromString(TEXT("Unknown"));
	}
}

FLinearColor URankFunctionLibrary::GetHitTypeColor(EHitType HitType)
{
	switch (HitType)
	{
	case EHitType::Lost:
		return FLinearColor(0.8f, 0.2f, 0.2f, 1.0f); // Красный
	case EHitType::Miss:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый
	case EHitType::Perfect:
		return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f); // Зеленый
	default:
		return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Серый по умолчанию
	}
}

ETrackRank URankFunctionLibrary::CalculateTrackRank(const TMap<EHitType, int32>& HitTypeCounts, int32 TotalBeats)
{
	if (TotalBeats <= 0) return ETrackRank::None;
	int32 Perfect = HitTypeCounts.Contains(EHitType::Perfect) ? HitTypeCounts[EHitType::Perfect] : 0;
	float Accuracy = static_cast<float>(Perfect) / static_cast<float>(TotalBeats);
	if (Accuracy >= 1.0f) return ETrackRank::SS;
	if (Accuracy >= 0.95f) return ETrackRank::S;
	if (Accuracy >= 0.90f) return ETrackRank::A;
	if (Accuracy >= 0.80f) return ETrackRank::B;
	if (Accuracy >= 0.70f) return ETrackRank::C;
	if (Accuracy >= 0.50f) return ETrackRank::D;
	return ETrackRank::E;
}
