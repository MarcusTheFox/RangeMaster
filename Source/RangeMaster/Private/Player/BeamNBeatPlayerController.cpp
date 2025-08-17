// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BeamNBeatPlayerController.h"

#include "Core/RangeMasterGameMode.h"
#include "FunctionLibraries/GameUtilityFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABeamNBeatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	SetInputMode_UI();

	if (IsLocalController() && HUDContainerClass)
	{
		HUDContainerInstance = CreateWidget<UUserWidget>(this, HUDContainerClass);
		if (HUDContainerInstance)
		{
			HUDContainerInstance->AddToViewport();
		}
	}

	ARangeMasterGameMode* GameMode = UGameUtilityFunctionLibrary::GetRangeMasterGameMode(this);

	if (!GameMode) return;

	GameMode->OnPreparePhaseStarted.AddDynamic(this, &ABeamNBeatPlayerController::OnPreparePhaseStarted);
	GameMode->OnGameFinished.AddDynamic(this, &ABeamNBeatPlayerController::OnGameFinished);
	GameMode->OnGameStopped.AddDynamic(this, &ABeamNBeatPlayerController::OnGameStopped);
	GameMode->OnGameReset.AddDynamic(this, &ABeamNBeatPlayerController::OnGameReset);
}

void ABeamNBeatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this,
		                                   &ABeamNBeatPlayerController::OnPauseAction);
	}
}

void ABeamNBeatPlayerController::GameResume()
{
	OnGameResumed.Broadcast();
	UGameplayStatics::SetGamePaused(this, false);
	SetInputMode_Game();
}

void ABeamNBeatPlayerController::GamePause()
{
	OnGamePaused.Broadcast();
	UGameplayStatics::SetGamePaused(this, true);
	SetInputMode_GameAndUI();
}

void ABeamNBeatPlayerController::OnPreparePhaseStarted()
{
	SetInputMode_Game();
	AddInputMappingContext(PauseMappingContext);
}

void ABeamNBeatPlayerController::OnGameFinished(const FGameResultData& Result)
{
	SetInputMode_UI();
	CenterCursor();
	RemoveInputMappingContext(PauseMappingContext);
}

void ABeamNBeatPlayerController::OnGameStopped()
{
	SetInputMode_UI();
	RemoveInputMappingContext(PauseMappingContext);
}

void ABeamNBeatPlayerController::OnGameReset()
{
	SetInputMode_Game();
	UGameplayStatics::SetGamePaused(this, false);
}

void ABeamNBeatPlayerController::OnPauseAction(const FInputActionValue& Value)
{
	if (UGameplayStatics::IsGamePaused(this))
	{
		GameResume();
	}
	else
	{
		GamePause();
	}
}

void ABeamNBeatPlayerController::SetInputMode_Game()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	
	bShowMouseCursor = false;
}

void ABeamNBeatPlayerController::SetInputMode_UI()
{
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	
	bShowMouseCursor = true;
}

void ABeamNBeatPlayerController::SetInputMode_GameAndUI()
{
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	
	bShowMouseCursor = true;
	CenterCursor();
}

void ABeamNBeatPlayerController::AddInputMappingContext(UInputMappingContext* MappingContext)
{
	Subsystem->AddMappingContext(MappingContext, 0);
}

void ABeamNBeatPlayerController::RemoveInputMappingContext(UInputMappingContext* MappingContext)
{
	Subsystem->RemoveMappingContext(MappingContext);
}

void ABeamNBeatPlayerController::CenterCursor()
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	const int32 CenterX = ViewportSizeX / 2;
	const int32 CenterY = ViewportSizeY / 2;
	
	SetMouseLocation(CenterX, CenterY);
}