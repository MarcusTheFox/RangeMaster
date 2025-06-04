#include "AC_ScoreSystem.h"

UAC_ScoreSystem::UAC_ScoreSystem()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    Score = 0;
    CurrentCombo = 0;
    MaxCombo = 0;
}

void UAC_ScoreSystem::BeginPlay()
{
    Super::BeginPlay();
    ResetAllStats();
}

void UAC_ScoreSystem::AddScore(const int32 Value)
{
    if (Value == 0) return;
    
    Score += Value;
    OnScoreChanged.Broadcast(Score);
}

int32 UAC_ScoreSystem::GetScore() const
{
    return Score;
}

void UAC_ScoreSystem::IncreaseCombo(int32 Amount)
{
    if (Amount <= 0) return;
    
    CurrentCombo += Amount;
    OnComboChanged.Broadcast(CurrentCombo);

    if (CurrentCombo > MaxCombo)
    {
        MaxCombo = CurrentCombo;
        OnMaxComboChanged.Broadcast(MaxCombo);
    }
}

void UAC_ScoreSystem::ResetCombo()
{
    if (CurrentCombo == 0) return;
    
    CurrentCombo = 0;
    OnComboChanged.Broadcast(CurrentCombo);
}

int32 UAC_ScoreSystem::GetCurrentCombo() const
{
    return CurrentCombo;
}

int32 UAC_ScoreSystem::GetMaxCombo() const
{
    return MaxCombo;
}

void UAC_ScoreSystem::ResetAllStats()
{
    Score = 0;
    CurrentCombo = 0;
    MaxCombo = 0;
    
    OnScoreChanged.Broadcast(Score);
    OnComboChanged.Broadcast(CurrentCombo);
    OnMaxComboChanged.Broadcast(MaxCombo);
}