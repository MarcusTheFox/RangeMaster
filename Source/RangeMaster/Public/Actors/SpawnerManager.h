// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerManager.generated.h"

USTRUCT(BlueprintType)
struct FSpawnerGridSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
	int32 GridSizeX = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
	int32 GridSizeY = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "100"))
	float SpacingX = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "100"))
	float SpacingY = 200.0f;
};

UCLASS()
class RANGEMASTER_API ASpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnerManager();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
	FSpawnerGridSettings GridSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Settings")
	TSubclassOf<AActor> SpawnerClass;

	UFUNCTION(CallInEditor, Category = "Spawner Management")
	void CreateSpawnerGrid();

	UFUNCTION(CallInEditor, Category = "Spawner Management")
	void ClearSpawnerGrid();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<AActor*> GetSpawners() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> Spawners;

	FVector CalculateSpawnerPosition(int32 IndexX, int32 IndexY) const;
}; 