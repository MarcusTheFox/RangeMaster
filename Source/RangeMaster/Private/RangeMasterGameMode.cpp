#include "RangeMasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/RhythmController.h"
#include "GameFunctionLibrary.h"
#include "TrackRank.h"

ARangeMasterGameMode::ARangeMasterGameMode()
{
    ScoreSystem = CreateDefaultSubobject<UScoreSystemComponent>(TEXT("ScoreSystem"));
}

void ARangeMasterGameMode::BeginPlay()
{
    Super::BeginPlay();
    RhythmController = Cast<ARhythmController>(UGameplayStatics::GetActorOfClass(this, ARhythmController::StaticClass()));
    if (RhythmController)
    {
        RhythmController->OnMusicFinished.AddDynamic(this, &ARangeMasterGameMode::HandleMusicFinished);
    }
}

void ARangeMasterGameMode::HandleMusicFinished()
{
    OnMusicFinished();
}

void ARangeMasterGameMode::StartGameRequest_Implementation()
{
    ResetHitTypeCounts();
    if (ScoreSystem)
    {
        ScoreSystem->ResetAllStats();
    }
    StartPreparePhase();
}

void ARangeMasterGameMode::StartPreparePhase()
{
    OnPreparePhaseStarted.Broadcast(); // UI: "Готовьтесь!"
    GetWorld()->GetTimerManager().SetTimer(PrepareTimerHandle, this, &ARangeMasterGameMode::StartCountdown, PreparePhaseTime, false);
}

void ARangeMasterGameMode::StartCountdown()
{
    OnPreparePhaseFinished.Broadcast(); // UI: подготовка закончилась
    OnCountdownStarted.Broadcast(); // UI: показать отсчёт
    CurrentCountdown = CountdownTime;
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ARangeMasterGameMode::CountdownTick, CountdownTickInterval, true);
}

void ARangeMasterGameMode::CountdownTick()
{
    CurrentCountdown -= CountdownTickInterval;
    FCountdownInfo Info;
    Info.TimeLeft = FMath::Max(0.0f, CurrentCountdown);
    Info.TotalTime = CountdownTime;
    Info.Progress = (CountdownTime > 0.f) ? 1.0f - (Info.TimeLeft / CountdownTime) : 1.0f;
    OnCountdownTick.Broadcast(Info);
    if (CurrentCountdown <= 0.0f)
    {
        FinishCountdown();
    }
}

void ARangeMasterGameMode::FinishCountdown()
{
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    OnCountdownFinished.Broadcast(); // UI: "Старт!"
    OnGameStarted.Broadcast(); // Сигнал о начале игры
    if (RhythmController)
    {
        RhythmController->PlayMusic();
    }
}

void ARangeMasterGameMode::ForceStopGame_Implementation()
{
    bWasForceStopped = true;
    if (RhythmController)
    {
        RhythmController->StopMusic();
    }
}

void ARangeMasterGameMode::OnMusicFinished()
{
    FName TrackID = TEXT("1"); // TODO: получить актуальный ID трека
    int32 Score = ScoreSystem ? ScoreSystem->GetScore() : 0;
    int32 TotalBeats = 0;
    int32 MissCount = GetHitTypeCount(EHitType::Miss);
    if (RhythmController && RhythmController->BeatMapTable)
    {
        TotalBeats = UGameFunctionLibrary::GetBeatMapCount(RhythmController->BeatMapTable);
    }
    ETrackRank Rank = UGameFunctionLibrary::CalculateTrackRank(HitTypeCounts, TotalBeats);
    if (!bWasForceStopped)
    {
        UGameFunctionLibrary::SaveTrackResult(TrackID, Score, Rank);
    }
    
    FGameResultData Result;
    Result.Score = Score;
    Result.Rank = Rank;
    Result.MaxCombo = ScoreSystem ? ScoreSystem->GetMaxCombo() : 0;
    Result.HitTypeCounts = HitTypeCounts;
    OnGameFinished.Broadcast(Result);
    bWasForceStopped = false;
}

void ARangeMasterGameMode::RegisterHit(EHitType HitType)
{
    int32& Count = HitTypeCounts.FindOrAdd(HitType);
    Count++;
    OnHitRegistered.Broadcast(HitType);
}

int32 ARangeMasterGameMode::GetHitTypeCount(EHitType HitType) const
{
    const int32* Count = HitTypeCounts.Find(HitType);
    return Count ? *Count : 0;
}

void ARangeMasterGameMode::ResetHitTypeCounts()
{
    HitTypeCounts.Empty();
} 