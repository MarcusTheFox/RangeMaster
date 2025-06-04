// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFunctionLibrary.h"

TArray<AActor*> UGameFunctionLibrary::SortActorArrayByLabel(TArray<AActor*>& Array, bool bAscending)
{
	if (Array.Num() == 0) return Array;

	Array.Sort([bAscending](const AActor& A, const AActor& B)
	{
		if (!A.IsValidLowLevel() || !B.IsValidLowLevel())
		{
			if (!A.IsValidLowLevel() && B.IsValidLowLevel()) return bAscending;
			if (A.IsValidLowLevel() && !B.IsValidLowLevel()) return !bAscending;
			return false;
		}

		FString ALabel = A.GetActorLabel();
		FString BLabel = B.GetActorLabel();

		if (bAscending)
		{
			return ALabel.Compare(BLabel, ESearchCase::IgnoreCase) < 0;
		}
		return ALabel.Compare(BLabel, ESearchCase::IgnoreCase) > 0;
	});

	return Array;
}
