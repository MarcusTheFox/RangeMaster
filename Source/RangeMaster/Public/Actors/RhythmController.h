#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Data/Structs/BeatMapData.h"
#include "Actors/SpawnerManager.h"
#include "Actors/Target.h"
#include "Core/Parsing/BeatMapParser.h"
#include "Data/Structs/TimeMapData.h"
#include "Data/Structs/TrackInfo.h"
#include "RhythmController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicFinished);

UCLASS()
class RANGEMASTER_API ARhythmController : public AActor
{
    GENERATED_BODY()
public:
    ARhythmController();

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Music")
    UAudioComponent* MusicComponent;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Music")
    FOnMusicFinished OnMusicFinished;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music")
    void StopMusic();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music")
    void PlayMusic();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music")
    void OnMusicPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music")
    void OnMusicPlaybackFinished();

    UFUNCTION()
    void HandleMusicPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent);

    UFUNCTION()
    void HandleMusicPlaybackFinished();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music|Spawning")
    void SpawnTargetsByBeatMap(float CurrentTime);

    UFUNCTION(BlueprintCallable, Category="Music|BeatMap")
    void SetTrackData(FTrackInfo TrackInfo);

private:
    static bool GetBeatMapFromTrackInfo(FTrackInfo TrackInfo, TArray<FBeatMapData>& OutBeatMap, FBeatMapSettings& OutSettings);
    static bool GetSoundWaveFromTrackInfo(FTrackInfo TrackInfo, USoundWave*& OutSoundWave);

    UFUNCTION()
    void RemoveTargetFromActiveList(ATarget* Target);

    UFUNCTION()
    void DestroyAllActiveTargets();

    UFUNCTION()
    bool IsGameFinished();
    
    UPROPERTY()
    ASpawnerManager* SpawnerManager = nullptr;

    UPROPERTY()
    TSubclassOf<ATarget> TargetClass;

    UPROPERTY()
    TArray<ASpawner*> CachedSpawners;
    
    UPROPERTY()
    TObjectPtr<USoundWave> CurrentSoundWave = nullptr;

    int32 LastSpawnedTargetIndex = 0;

    UPROPERTY()
    TArray<ATarget*> ActiveTargets;
    
    TArray<FTimeMapData> CachedTimeMap;
    
    bool bHasFinished = false;

    FTimerHandle StopGameTimer;
    float StopGameTime = 2.0f;
}; 