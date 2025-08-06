#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/Enums/HitType.h"
#include "Components/ScoreSystemComponent.h"
#include "Data/Structs/GameResultData.h"
#include "Data/Structs/CountdownInfo.h"
#include "Data/Structs/TrackDataRow.h"
#include "Data/Structs/TrackInfo.h"
#include "RangeMasterGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitRegistered, EHitType, HitType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinished, const FGameResultData&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountdownTick, const FCountdownInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreparePhaseStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreparePhaseFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStarted);

UCLASS()
class ARangeMasterGameMode : public AGameModeBase
{
    GENERATED_BODY()
    
public:
    ARangeMasterGameMode();

    virtual void BeginPlay() override;

    void OnMusicFinished();

    UFUNCTION()
    void HandleMusicFinished();

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

    UPROPERTY(BlueprintReadOnly, Category="Game")
    TMap<EHitType, int32> HitTypeCounts;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game")
    UScoreSystemComponent* ScoreSystem;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Game")
    class ARhythmController* RhythmController = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game")
    FTrackInfo CurrentTrackData;

    // === ДЛЯ ПЛАВНОГО ОТСЧЁТА ===

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
    bool bWasForceStopped = false;
    FTimerHandle PrepareTimerHandle;
    FTimerHandle CountdownTimerHandle;
    float CountdownTime = 3.0f; // Длительность отсчёта (сек)
    float CurrentCountdown = 0.0f;
    float CountdownTickInterval = 0.01f; // Интервал тика для плавности
    float PreparePhaseTime = 2.0f; // Длительность подготовки (сек)

    void StartPreparePhase();
    void StartCountdown();
    void CountdownTick();
    void FinishCountdown();
}; 