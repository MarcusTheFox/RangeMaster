#pragma once

#include "CoreMinimal.h"
#include "Data/Structs/BeatMapData.h"
#include "Data/Structs/BeatMapTypes.h"

class FBeatMapParser
{
public:
	static bool Parse(const TArray<FString>& Lines, TArray<FBeatMapData>& OutBeatMap, FBeatMapSettings& OutSettings);
	static int32 CountTargets(const TArray<FString>& Lines);
	
private:
	static void ParseHeader(const TArray<FString>& Lines, int32& InOutLineIndex, FBeatMapSettings& OutSettings);
	static void ParseNotes(const TArray<FString>& Lines, int32 StartLineIndex, const FBeatMapSettings& Settings,
		TArray<FBeatMapData>& OutBeatMap);
	static void ParseNoteEvent(const FString& NoteEventString, float TotalBeat, float BpmForThisTimestamp,
		const FBeatMapSettings& Settings, TArray<FBeatMapData>& OutBeatMap);
	static bool LineIsComment(const FString& Line);
};
