#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/BeatMapData.h"

struct FBeatMapSettings
{
	float BPM = 120.0f;
	int32 DefaultPower = 1500;
	float TimeOffset = 0.0f;
};

class FBeatMapParser
{
public:
	static bool Parse(const TArray<FString>& Lines, TArray<FBeatMapData>& OutBeatMap);
	static int32 CountTargets(const TArray<FString>& Lines);
	
private:
	static void ParseHeader(const TArray<FString>& Lines, int32& InOutLineIndex, FBeatMapSettings& OutSettings);
	static void ParseNotes(const TArray<FString>& Lines, int32 StartLineIndex, const FBeatMapSettings& Settings,
		TArray<FBeatMapData>& OutBeatMap);
	static void ParseNoteEvent(const FString& NoteEventString, float TotalBeat, float BpmForThisTimestamp,
		const FBeatMapSettings& Settings, TArray<FBeatMapData>& OutBeatMap);
	static bool LineIsComment(const FString& Line);
};
