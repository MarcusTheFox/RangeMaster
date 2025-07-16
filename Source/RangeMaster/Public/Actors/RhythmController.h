#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "Data/BeatMapData.h"
#include "Actors/SpawnerManager.h"
#include "Actors/Target.h"
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

private:
    UPROPERTY()
    ASpawnerManager* SpawnerManager = nullptr;

    UPROPERTY()
    TArray<ASpawner*> CachedSpawners;

    int32 LastSpawnedBeatIndex = 0;
    TArray<FBeatMapData> CachedBeatMap;
}; 