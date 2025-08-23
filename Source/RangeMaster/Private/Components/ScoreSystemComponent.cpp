#include "Components/ScoreSystemComponent.h"

#include "Settings/BeamNBeatScoreSettings.h"

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

void UScoreSystemComponent::SubtractScore(int32 Value)
{
    if (Value == 0) return;
    
    Score = FMath::Max(0, Score - Value);
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
    const UBeamNBeatScoreSettings* Settings = UBeamNBeatScoreSettings::Get();
    if (!Settings) return 1;
    
    for (int32 i = Settings->ComboTiers.Num() - 1; i >= 0; --i)
    {
        const FComboTierData& Tier = Settings->ComboTiers[i];
        if (CurrentCombo >= Tier.Threshold)
        {
            return Tier.Multiplier;
        }
    }
    
    return Settings->BaseMultiplier;
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