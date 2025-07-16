// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "RangeMasterGameMode.h"

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
		return FLinearColor(1.0f, 0.84f, 0.0f, 1.0f); // Золотой
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

void UGameFunctionLibrary::SaveTrackResult(FName TrackID, int32 Score, ETrackRank Rank)
{
	URangeMasterSaveGame* SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("RangeMasterSave"), 0));
	if (!SaveGame)
	{
		SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::CreateSaveGameObject(URangeMasterSaveGame::StaticClass()));
	}
	
	if (SaveGame)
	{
		if (SaveGame->TrackResults.Contains(TrackID))
		{
			FTrackSaveData& ExistingData = SaveGame->TrackResults[TrackID];
			
			if (Score > ExistingData.MaxScore)
			{
				ExistingData.MaxScore = Score;
				ExistingData.MaxRank = Rank;
			}
		}
		else
		{
			FTrackSaveData NewData;
			NewData.MaxScore = Score;
			NewData.MaxRank = Rank;
			SaveGame->TrackResults.Add(TrackID, NewData);
		}
		
		UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("RangeMasterSave"), 0);
		
		UE_LOG(LogTemp, Log, TEXT("Track result saved: %s - Score: %d, Rank: %d"), *TrackID.ToString(), Score, (int32)Rank);
	}
}

bool UGameFunctionLibrary::GetTrackResult(FName TrackID, FTrackSaveData& OutResult)
{
	URangeMasterSaveGame* SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("RangeMasterSave"), 0));
	
	if (SaveGame && SaveGame->TrackResults.Contains(TrackID))
	{
		OutResult = SaveGame->TrackResults[TrackID];
		return true;
	}
	
	return false;
}

TArray<FBeatMapData> UGameFunctionLibrary::GetBeatMapData(UDataTable* BeatMapTable)
{
	TArray<FBeatMapData> BeatMapData;
	
	if (BeatMapTable)
	{
		TArray<FBeatMapData*> RowPtrs;
		BeatMapTable->GetAllRows<FBeatMapData>(TEXT("GetBeatMapData"), RowPtrs);
		
		for (FBeatMapData* RowPtr : RowPtrs)
		{
			if (RowPtr)
			{
				BeatMapData.Add(*RowPtr);
			}
		}
	}
	
	return BeatMapData;
}

float UGameFunctionLibrary::GetBeatMapDuration(UDataTable* BeatMapTable)
{
	TArray<FBeatMapData> BeatMapData = GetBeatMapData(BeatMapTable);
	
	if (BeatMapData.Num() == 0)
	{
		return 0.0f;
	}
	
	float MaxTime = 0.0f;
	for (const FBeatMapData& BeatData : BeatMapData)
	{
		if (BeatData.Time > MaxTime)
		{
			MaxTime = BeatData.Time;
		}
	}
	
	return MaxTime;
}

int32 UGameFunctionLibrary::GetBeatMapCount(UDataTable* BeatMapTable)
{
	TArray<FBeatMapData> BeatMapData = GetBeatMapData(BeatMapTable);
	return BeatMapData.Num();
}

ARangeMasterGameMode* UGameFunctionLibrary::GetRangeMasterGameMode(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;
    UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    return Cast<ARangeMasterGameMode>(UGameplayStatics::GetGameMode(World));
}

ETrackRank UGameFunctionLibrary::CalculateTrackRank(const TMap<EHitType, int32>& HitTypeCounts, int32 TotalBeats)
{
    if (TotalBeats <= 0) return ETrackRank::None;
    int32 Perfect = HitTypeCounts.Contains(EHitType::Perfect) ? HitTypeCounts[EHitType::Perfect] : 0;
    float Accuracy = (float)Perfect / (float)TotalBeats;
    if (Accuracy >= 1.0f) return ETrackRank::SS;
    if (Accuracy >= 0.95f) return ETrackRank::S;
    if (Accuracy >= 0.90f) return ETrackRank::A;
    if (Accuracy >= 0.80f) return ETrackRank::B;
    if (Accuracy >= 0.70f) return ETrackRank::C;
    if (Accuracy >= 0.50f) return ETrackRank::D;
    return ETrackRank::E;
}