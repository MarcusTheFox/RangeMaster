// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GameSaveFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGame/RangeMasterSaveGame.h"

void UGameSaveFunctionLibrary::SaveTrackResult(FName TrackID, int32 Score, ETrackRank Rank)
{
	const FString SaveSlot = TrackID.ToString();
	URangeMasterSaveGame* SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (!SaveGame)
	{
		SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::CreateSaveGameObject(URangeMasterSaveGame::StaticClass()));
	}
	
	if (SaveGame)
	{
		FTrackSaveData& ExistingData = SaveGame->TrackResult;
		
		if (Score > ExistingData.MaxScore)
		{
			ExistingData.MaxScore = Score;
			ExistingData.MaxRank = Rank;
		}
		
		UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlot, 0);
		
		UE_LOG(LogTemp, Log, TEXT("Track result saved: %s - Score: %d, Rank: %d"), *SaveSlot, Score, (int32)Rank);
	}
}

bool UGameSaveFunctionLibrary::GetTrackResult(FName TrackID, FTrackSaveData& OutResult)
{
	const FString SaveSlot = TrackID.ToString();
	const URangeMasterSaveGame* SaveGame = Cast<URangeMasterSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	
	if (SaveGame)
	{
		OutResult = SaveGame->TrackResult;
		return true;
	}
	
	return false;
}
