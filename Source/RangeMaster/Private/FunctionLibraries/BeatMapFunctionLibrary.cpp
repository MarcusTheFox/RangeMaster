// Fill out your copyright notice in the Description page of Project Settings.


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

TArray<FTrackDataRow> UBeatMapFunctionLibrary::GetTrackData(UDataTable* TrackDataTable)
{
	return GetDataFromDataTable<FTrackDataRow>(TrackDataTable);
}

TArray<FBeatMapData> UBeatMapFunctionLibrary::GetBeatMapData(UDataTable* BeatMapTable)
{
	return GetDataFromDataTable<FBeatMapData>(BeatMapTable);
}

TArray<FTimeMapData> UBeatMapFunctionLibrary::GetTimeMapData(UDataTable* BeatMapTable)
{
	return ConvertBeatMapToBeatTimes(GetBeatMapData(BeatMapTable), 0);
}

TArray<FTimeMapData> UBeatMapFunctionLibrary::ConvertBeatMapToBeatTimes(TArray<FBeatMapData> BeatMapData, float TimeOffsetMs)
{
	TArray<FTimeMapData> BeatTimes;
	if (BeatMapData.Num() == 0) return BeatTimes;

	BeatTimes.Reserve(BeatMapData.Num());
	
	double CurrentTime = TimeOffsetMs / 1000.0;

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