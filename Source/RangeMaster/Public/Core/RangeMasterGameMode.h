#pragma once

#include "CoreMinimal.h"
#include "Actors/RhythmController.h"
#include "Components/ScoreSystemComponent.h"
#include "Data/Enums/HitType.h"
#include "Data/Structs/CountdownInfo.h"
#include "Data/Structs/GameResultData.h"
#include "Data/Structs/TimeMapData.h"
#include "Data/Structs/TrackInfo.h"
#include "GameFramework/GameModeBase.h"
#include "RangeMasterGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitRegistered, EHitType, HitType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinished, const FGameResultData&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountdownTick, const FCountdownInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreparePhaseStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreparePhaseFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStopped);

UCLASS()
class ARangeMasterGameMode : public AGameModeBase
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    
public:
    ARangeMasterGameMode();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Game")
    void StartGameRequest(FTrackInfo TrackInfo);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Game")
    void ForceStopGame();

    UFUNCTION(BlueprintCallable, Category="Game")
    void RegisterHit(EHitType HitType);

    UFUNCTION(BlueprintCallable, Category="Game")
    int32 GetHitTypeCount(EHitType HitType) const;

    UFUNCTION(BlueprintCallable, Category="Game")
    void ResetHitTypeCounts();

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game")
    FOnHitRegistered OnHitRegistered;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game")
    FOnGameFinished OnGameFinished;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game")
    FOnGameStarted OnGameStarted;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game")
    FOnGameStopped OnGameStopped;

    UPROPERTY(BlueprintReadOnly, Category="Game")
    TMap<EHitType, int32> HitTypeCounts;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game")
    UScoreSystemComponent* ScoreSystem;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game")
    FTrackInfo CurrentTrackData;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game|Countdown")
    FOnCountdownStarted OnCountdownStarted;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game|Countdown")
    FOnCountdownTick OnCountdownTick;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game|Countdown")
    FOnCountdownFinished OnCountdownFinished;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game|Countdown")
    FOnPreparePhaseStarted OnPreparePhaseStarted;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Game|Countdown")
    FOnPreparePhaseFinished OnPreparePhaseFinished;

private:
    void EndGame();
    void DestroyAllActiveTargets();
    
    UFUNCTION()
    void OnBeatReceived(const FTimeMapData& TimeMapData);

    UFUNCTION()
    void HandleMusicFinished();

    UFUNCTION()
    void OnTargetDestroyed(ATarget* Target);
    
    void StartPreparePhase();
    void StartCountdown();
    void CountdownTick();
    void FinishCountdown();

    UPROPERTY()
    ARhythmController* RhythmController = nullptr;

    UPROPERTY()
    ASpawnerManager* SpawnerManager = nullptr;

    UPROPERTY()
    TArray<TObjectPtr<ASpawner>> CachedSpawners;

    UPROPERTY()
    TArray<TObjectPtr<ATarget>> ActiveTargets;

    UPROPERTY()
    TSubclassOf<ATarget> TargetClass;
    
    bool bWasForceStopped = false;
    bool bMusicHasFinished = false;
    int32 TotalTargets = 0;
    int32 LastSpawnedTargetIndex = 0;
    
    FTimerHandle PrepareTimerHandle;
    FTimerHandle CountdownTimerHandle;
    FTimerHandle EndGameTimerHandle;
    
    float CountdownTime = 3.0f;
    float CurrentCountdown = 0.0f;
    float CountdownTickInterval = 0.01f;
    float PreparePhaseTime = 2.0f;
    float EndGameTime = 1.0f;
}; 