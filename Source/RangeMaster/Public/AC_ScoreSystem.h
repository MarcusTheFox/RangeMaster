#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_ScoreSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedDelegate, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboChangedDelegate, int32, NewCombo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxComboChangedDelegate, int32, NewMaxCombo);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANGEMASTER_API UAC_ScoreSystem : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_ScoreSystem();

protected:
    virtual void BeginPlay() override;

public:    
    UFUNCTION(BlueprintCallable, Category="Score System|Score")
    void AddScore(int32 Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Score System|Score")
    int32 GetScore() const;

    UFUNCTION(BlueprintCallable, Category="Score System|Combo")
    void IncreaseCombo(int32 Amount = 1);

    UFUNCTION(BlueprintCallable, Category="Score System|Combo")
    void ResetCombo();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Score System|Combo")
    int32 GetCurrentCombo() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Score System|Combo")
    int32 GetMaxCombo() const;

    UFUNCTION(BlueprintCallable, Category="Score System|Control")
    void ResetAllStats();

    UPROPERTY(BlueprintAssignable, Category="Score System|Events")
    FOnScoreChangedDelegate OnScoreChanged;

    UPROPERTY(BlueprintAssignable, Category="Score System|Events")
    FOnComboChangedDelegate OnComboChanged;

    UPROPERTY(BlueprintAssignable, Category="Score System|Events")
    FOnMaxComboChangedDelegate OnMaxComboChanged;

private:
    UPROPERTY(VisibleAnywhere, Category="Score System|State", meta=(AllowPrivateAccess = "true")) // VisibleAnywhere, чтобы видеть в деталях для отладки
    int32 Score;

    UPROPERTY(VisibleAnywhere, Category="Score System|State", meta=(AllowPrivateAccess = "true"))
    int32 CurrentCombo;

    UPROPERTY(VisibleAnywhere, Category="Score System|State", meta=(AllowPrivateAccess = "true"))
    int32 MaxCombo;
};