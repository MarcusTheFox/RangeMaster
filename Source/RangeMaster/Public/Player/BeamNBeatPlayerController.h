// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/Structs/GameResultData.h"
#include "BeamNBeatPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);

/**
 * 
 */
UCLASS()
class RANGEMASTER_API ABeamNBeatPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void GameResume();

	UFUNCTION(BlueprintCallable)
	void GamePause();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OnPreparePhaseStarted();
	
	UFUNCTION()
	void OnGameFinished(const FGameResultData& Result);
	
	UFUNCTION()
	void OnGameStopped();
	
	UFUNCTION()
	void OnGameReset();

	UFUNCTION()
	void OnPauseAction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputMode_Game();
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputMode_UI();
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputMode_GameAndUI();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddInputMappingContext(UInputMappingContext* MappingContext);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void RemoveInputMappingContext(UInputMappingContext* MappingContext);
	
	UFUNCTION(BlueprintCallable, Category = "UI|Cursor")
	void CenterCursor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Game")
	FOnGameResumed OnGameResumed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Game")
	FOnGamePaused OnGamePaused;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDContainerClass;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> HUDContainerInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> PauseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> PauseAction;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem;
};
