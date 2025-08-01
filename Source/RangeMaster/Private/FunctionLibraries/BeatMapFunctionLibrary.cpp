﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/BeatMapFunctionLibrary.h"

#include "Algo/Count.h"

template <typename T>
TArray<T> UBeatMapFunctionLibrary::GetDataFromDataTable(UDataTable* DataTable)
{
	TArray<T> Data;
	
	if (DataTable)
	{
		TArray<T*> RowPtrs;
		DataTable->GetAllRows<T>(TEXT("GetDataFromDataTable"), RowPtrs);
		
		for (T* RowPtr : RowPtrs)
		{
			if (RowPtr)
			{
				Data.Add(*RowPtr);
			}
		}
	}
	
	return Data;
}

inline TArray<FTrackDataRow> UBeatMapFunctionLibrary::GetTrackData(UDataTable* TrackDataTable)
{
	return GetDataFromDataTable<FTrackDataRow>(TrackDataTable);
}

inline TArray<FBeatMapData> UBeatMapFunctionLibrary::GetBeatMapData(UDataTable* BeatMapTable)
{
	return GetDataFromDataTable<FBeatMapData>(BeatMapTable);
}

inline TArray<FTimeMapData> UBeatMapFunctionLibrary::GetTimeMapData(UDataTable* BeatMapTable)
{
	return ConvertBeatMapToBeatTimes(GetBeatMapData(BeatMapTable));
}

inline TArray<FTimeMapData> UBeatMapFunctionLibrary::ConvertBeatMapToBeatTimes(TArray<FBeatMapData> BeatMapData)
{
	TArray<FTimeMapData> BeatTimes;
	if (BeatMapData.Num() == 0) return BeatTimes;

	BeatTimes.Reserve(BeatMapData.Num());

	double CurrentTime = 0.0f;
	float PreviousBeat = 0.0f;
	float CurrentBPM = 120.0f;
	
	if (BeatMapData[0].BPM > 0.0f)
	{
		CurrentBPM = BeatMapData[0].BPM;
	}

	for (const FBeatMapData& Data: BeatMapData)
	{
		const float Beat = Data.BeatIndex + Data.BeatFraction;
		const float DeltaBeat = Beat - PreviousBeat;

		if (CurrentBPM > 0.0f)
		{
			const float SecondsPerBeat = 60.0f / CurrentBPM;
			CurrentTime += DeltaBeat * SecondsPerBeat;
		}
		if (Data.BPM > 0.0f)
		{
			CurrentBPM = Data.BPM;
		}
        
		FTimeMapData NewTimeData;
		NewTimeData.SpawnerID = Data.SpawnerID;
		NewTimeData.ShotPower = Data.ShotPower;
		NewTimeData.Time = CurrentTime;
		
		BeatTimes.Add(NewTimeData);

		PreviousBeat = Beat;
	}

	return BeatTimes;
}

inline float UBeatMapFunctionLibrary::GetBeatMapDuration(UDataTable* BeatMapTable)
{
	TArray<FTimeMapData> BeatMapData = GetTimeMapData(BeatMapTable);
	
	if (BeatMapData.Num() == 0)
	{
		return 0.0f;
	}
	
	float MaxTime = 0.0f;
	for (const FTimeMapData& BeatData : BeatMapData)
	{
		if (BeatData.Time > MaxTime)
		{
			MaxTime = BeatData.Time;
		}
	}
	
	return MaxTime;
}

inline int32 UBeatMapFunctionLibrary::GetTotalTargetCount(UDataTable* BeatMapTable)
{
	const TArray<FBeatMapData> BeatMapData = GetBeatMapData(BeatMapTable);
	return Algo::CountIf(BeatMapData, [](const FBeatMapData& Data)
	{
		return Data.ShotPower > 0.0f;
	});
}