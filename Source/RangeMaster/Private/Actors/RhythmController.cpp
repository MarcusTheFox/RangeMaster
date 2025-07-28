#include "Actors/RhythmController.h"
#include "Actors/SpawnerManager.h"
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
    LastSpawnedTargetIndex = 0;
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
}

void ARhythmController::SpawnTargetsByBeatMap_Implementation(float CurrentTime, TSubclassOf<ATarget> TargetClass)
{
    if (CachedSpawners.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CachedSpawners is empty!"));
        return;
    }
    if (CachedTimeMap.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CachedTimeMap is empty!"));
        return;
    }
    while (LastSpawnedTargetIndex < CachedTimeMap.Num())
    {
        const FTimeMapData& Data = CachedTimeMap[LastSpawnedTargetIndex];
        if (Data.Time <= CurrentTime)
        {
            ++LastSpawnedTargetIndex;
            if (Data.ShotPower == 0) continue;
            if (CachedSpawners.IsValidIndex(Data.SpawnerID) && CachedSpawners[Data.SpawnerID])
            {
                CachedSpawners[Data.SpawnerID]->SpawnTarget(TargetClass, Data.ShotPower);
            }
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
    if (BeatMapTable)
    {
        CachedTimeMap = UGameFunctionLibrary::GetTimeMapData(BeatMapTable);
    }
    else
    {
        CachedTimeMap.Empty();
    }

    LastSpawnedTargetIndex = 0;
}

void ARhythmController::SetTrackData(FTrackDataRow TrackData)
{
    SetBeatMapTable(TrackData.BeatMap);
    MusicComponent->SetSound(TrackData.SoundWave);
}
