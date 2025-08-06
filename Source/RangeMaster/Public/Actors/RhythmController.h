#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "Data/Structs/BeatMapData.h"
#include "Actors/SpawnerManager.h"
#include "Actors/Target.h"
#include "Data/Structs/TimeMapData.h"
#include "Data/Structs/TrackDataRow.h"
#include "Data/Structs/TrackInfo.h"
#include "Sound/SoundWaveProcedural.h"
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

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Music|BeatMap")
    UDataTable* BeatMapTable = nullptr;

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

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music")
    void TrySpawnTargetAtTime(float CurrentTime);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Music|Spawning")
    void SpawnTargetsByBeatMap(float CurrentTime, TSubclassOf<ATarget> TargetClass);

    UFUNCTION(BlueprintCallable, Category="Music|BeatMap")
    void SetBeatMapTable(UDataTable* InTable);

    UFUNCTION(BlueprintCallable, Category="Music|BeatMap")
    void SetTrackData(FTrackInfo TrackInfo);

private:
    static bool GetBeatMapFromTrackInfo(FTrackInfo TrackInfo, TArray<FBeatMapData>& OutBeatMap);
    static bool GetSoundWaveFromTrackInfo(FTrackInfo TrackInfo, USoundWave*& OutSoundWave);
    
    UPROPERTY()
    ASpawnerManager* SpawnerManager = nullptr;

    UPROPERTY()
    TArray<ASpawner*> CachedSpawners;
    
    UPROPERTY()
    TObjectPtr<USoundWave> CurrentSoundWave = nullptr;

    int32 LastSpawnedTargetIndex = 0;
    TArray<FTimeMapData> CachedTimeMap;
    bool bHasFinished = false;
}; 