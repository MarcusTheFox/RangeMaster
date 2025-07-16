#include "Actors/RhythmController.h"
#include "Actors/SpawnerManager.h"
#include "EngineUtils.h"
#include "GameFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ARhythmController::ARhythmController()
{
    PrimaryActorTick.bCanEverTick = false;

    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->SetupAttachment(RootComponent);
    MusicComponent->bAutoActivate = false;
}

void ARhythmController::StopMusic_Implementation()
{
    if (MusicComponent)
    {
        MusicComponent->Stop();
    }
}

void ARhythmController::PlayMusic_Implementation()
{
    LastSpawnedBeatIndex = 0;
    if (MusicComponent)
    {
        MusicComponent->Play();
    }
}

void ARhythmController::BeginPlay()
{
    Super::BeginPlay();
    SpawnerManager = Cast<ASpawnerManager>(UGameplayStatics::GetActorOfClass(this, ASpawnerManager::StaticClass()));
    if (!SpawnerManager)
    {
        UE_LOG(LogTemp, Error, TEXT("SpawnerManager not found in world!"));
    }
    else
    {
        CachedSpawners = SpawnerManager->GetSpawners();
    }
    if (MusicComponent)
    {
        MusicComponent->OnAudioPlaybackPercent.AddDynamic(this, &ARhythmController::HandleMusicPlaybackPercent);
        MusicComponent->OnAudioFinished.AddDynamic(this, &ARhythmController::HandleMusicPlaybackFinished);
    }
}

void ARhythmController::HandleMusicPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent)
{
    OnMusicPlaybackPercent(PlayingSoundWave, PlaybackPercent);
}

void ARhythmController::HandleMusicPlaybackFinished()
{
    OnMusicPlaybackFinished();
}

void ARhythmController::OnMusicPlaybackPercent_Implementation(const USoundWave* PlayingSoundWave, float PlaybackPercent)
{
    float CurrentTime = 0.f;
    if (PlayingSoundWave)
    {
        CurrentTime = PlaybackPercent * PlayingSoundWave->Duration;
    }
    TrySpawnTargetAtTime(CurrentTime);
}

void ARhythmController::OnMusicPlaybackFinished_Implementation()
{
    OnMusicFinished.Broadcast();
}

void ARhythmController::TrySpawnTargetAtTime_Implementation(float CurrentTime)
{
    // TODO: Проверить битмап и заспавнить цель, если пора
}

void ARhythmController::SpawnTargetsByBeatMap_Implementation(float CurrentTime, TSubclassOf<ATarget> TargetClass)
{
    if (CachedSpawners.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CachedSpawners is empty!"));
        return;
    }
    if (CachedBeatMap.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CachedBeatMap is empty!"));
        return;
    }
    while (LastSpawnedBeatIndex < CachedBeatMap.Num())
    {
        const FBeatMapData& Beat = CachedBeatMap[LastSpawnedBeatIndex];
        if (Beat.Time <= CurrentTime)
        {
            if (CachedSpawners.IsValidIndex(Beat.SpawnerID) && CachedSpawners[Beat.SpawnerID])
            {
                CachedSpawners[Beat.SpawnerID]->SpawnTarget(TargetClass, Beat.ShotPower);
            }
            ++LastSpawnedBeatIndex;
        }
        else
        {
            break;
        }
    }
}

void ARhythmController::SetBeatMapTable(UDataTable* InTable)
{
    BeatMapTable = InTable;
    CachedBeatMap = BeatMapTable ? UGameFunctionLibrary::GetBeatMapData(BeatMapTable) : TArray<FBeatMapData>();
    LastSpawnedBeatIndex = 0;
} 