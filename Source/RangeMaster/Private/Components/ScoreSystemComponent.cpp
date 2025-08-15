#include "Components/ScoreSystemComponent.h"

UScoreSystemComponent::UScoreSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    Score = 0;
    CurrentCombo = 0;
    MaxCombo = 0;
}

void UScoreSystemComponent::BeginPlay()
{
    Super::BeginPlay();
    ResetAllStats();
}

void UScoreSystemComponent::AddScore(const int32 Value)
{
    if (Value == 0) return;
    
    Score += Value;
    OnScoreChanged.Broadcast(Score);
}

int32 UScoreSystemComponent::GetScore() const
{
    return Score;
}

void UScoreSystemComponent::IncreaseCombo(int32 Amount)
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

void UScoreSystemComponent::ResetCombo()
{
    if (CurrentCombo == 0) return;
    
    CurrentCombo = 0;
    OnComboChanged.Broadcast(CurrentCombo);
}

int32 UScoreSystemComponent::GetCurrentCombo() const
{
    return CurrentCombo;
}

int32 UScoreSystemComponent::GetMaxCombo() const
{
    return MaxCombo;
}

int32 UScoreSystemComponent::GetComboMultiplier() const
{
    if (CurrentCombo > 100)
        return 8;
    if (CurrentCombo > 50)
        return 5;
    if (CurrentCombo > 25)
        return 3;
    if (CurrentCombo > 10)
        return 2;
    return 1;
}

void UScoreSystemComponent::ResetAllStats()
{
    Score = 0;
    CurrentCombo = 0;
    MaxCombo = 0;
    
    OnScoreChanged.Broadcast(Score);
    OnComboChanged.Broadcast(CurrentCombo);
    OnMaxComboChanged.Broadcast(MaxCombo);
}