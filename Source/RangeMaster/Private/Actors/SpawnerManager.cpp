// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/SpawnerManager.h"
#include "Components/ChildActorComponent.h"

ASpawnerManager::ASpawnerManager()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
	Spawners.Empty();
	TArray<UChildActorComponent*> Components;
	GetComponents<UChildActorComponent>(Components);
	
	for (UChildActorComponent* Component : Components)
	{
		if (Component && Component->GetChildActor())
		{
			Spawners.Add(Component->GetChildActor());
		}
	}
	
	Algo::Reverse(Spawners);
}

void ASpawnerManager::CreateSpawnerGrid()
{
	ClearSpawnerGrid();

	if (!SpawnerClass)
	{
		return;
	}

	for (int32 Y = 0; Y < GridSettings.GridSizeY; Y++)
	{
		for (int32 X = 0; X < GridSettings.GridSizeX; X++)
		{
			FVector SpawnLocation = CalculateSpawnerPosition(X, Y);

			UChildActorComponent* ChildComponent = NewObject<UChildActorComponent>(this);
			ChildComponent->SetChildActorClass(SpawnerClass);
			ChildComponent->RegisterComponent();
			ChildComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			ChildComponent->SetRelativeLocation(SpawnLocation);

			AActor* SpawnedActor = ChildComponent->GetChildActor();
			if (SpawnedActor)
			{
				Spawners.Add(SpawnedActor);
			}
		}
	}
}

void ASpawnerManager::ClearSpawnerGrid()
{
	TArray<UChildActorComponent*> Components;
	GetComponents<UChildActorComponent>(Components);

	for (UChildActorComponent* Component : Components)
	{
		if (Component)
		{
			Component->DestroyComponent();
		}
	}

	Spawners.Empty();
}

TArray<AActor*> ASpawnerManager::GetSpawners() const
{
	return Spawners;
}

FVector ASpawnerManager::CalculateSpawnerPosition(int32 IndexX, int32 IndexY) const
{
	float PosX = IndexX * GridSettings.SpacingX;
	float PosY = IndexY * GridSettings.SpacingY;
	return FVector(PosX, PosY, 0.0f);
} 