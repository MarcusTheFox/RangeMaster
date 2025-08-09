#include "Actors/RhythmController.h"

#include "Actors/SpawnerManager.h"
#include "Components/AudioComponent.h"
#include "FunctionLibraries/BeatMapFunctionLibrary.h"
#include "FunctionLibraries/TrackFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWaveProcedural.h"

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
    DestroyAllActiveTargets();
}

void ARhythmController::PlayMusic_Implementation()
{
    bHasFinished = false; 
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
    if (bHasFinished || !CurrentSoundWave)
    {
        return;
    }

    if (CurrentSoundWave->IsA<USoundWaveProcedural>())
    {
        if (PlaybackPercent >= 1.0f)
        {
            MusicComponent->Stop();
            return;
        }
    }
    
    OnMusicPlaybackPercent(PlayingSoundWave, PlaybackPercent);
}

void ARhythmController::HandleMusicPlaybackFinished()
{
    if (bHasFinished)
    {
        return;
    }
    bHasFinished = true;

    if (IsGameFinished())
    {
        GetWorld()->GetTimerManager().SetTimer(StopGameTimer, this, &ARhythmController::OnMusicPlaybackFinished, StopGameTime, false);
    }
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
                ATarget* NewTarget = CachedSpawners[Data.SpawnerID]->SpawnTarget(TargetClass, Data.ShotPower);
                NewTarget->OnTargetDestroyed.AddDynamic(this, &ARhythmController::RemoveTargetFromActiveList);
                ActiveTargets.Add(NewTarget);
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
        CachedTimeMap = UBeatMapFunctionLibrary::GetTimeMapData(BeatMapTable);
    }
    else
    {
        CachedTimeMap.Empty();
    }

    LastSpawnedTargetIndex = 0;
}

void ARhythmController::SetTrackData(FTrackInfo TrackInfo)
{
    TArray<FBeatMapData> BeatMap;
    USoundWave* SoundWave;
    FBeatMapSettings BeatMapSettings;
    
    if (!GetBeatMapFromTrackInfo(TrackInfo, BeatMap, BeatMapSettings)) return;
    if (!GetSoundWaveFromTrackInfo(TrackInfo, SoundWave)) return;
    
    CurrentSoundWave = SoundWave;
    CachedTimeMap = UBeatMapFunctionLibrary::ConvertBeatMapToBeatTimes(BeatMap, BeatMapSettings.TimeOffsetMs);
    MusicComponent->SetSound(CurrentSoundWave);
}

bool ARhythmController::GetBeatMapFromTrackInfo(FTrackInfo TrackInfo, TArray<FBeatMapData>& OutBeatMap, FBeatMapSettings& OutSettings)
{
    const FString TracksDir = FPaths::Combine(FPaths::ProjectDir(), "UserTracks");
    if (!UTrackFunctionLibrary::LoadBeatMapForTrack(TrackInfo, TracksDir, OutBeatMap, OutSettings))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load beatmap for track: %s"), *TrackInfo.TrackID.ToString());
        return false;
    }
    
    return true;
}

bool ARhythmController::GetSoundWaveFromTrackInfo(FTrackInfo TrackInfo, USoundWave*& OutSoundWave)
{
    const FString TracksDir = FPaths::Combine(FPaths::ProjectDir(), "UserTracks");
    const FString AudioPath = FPaths::Combine(TracksDir, TrackInfo.TrackID.ToString(), TrackInfo.AudioFile);
    OutSoundWave = UTrackFunctionLibrary::CreateProceduralSoundWave(AudioPath);
    if (!OutSoundWave)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load audio for track: %s"), *TrackInfo.TrackID.ToString());
        return false;
    }

    return true;
}

void ARhythmController::RemoveTargetFromActiveList(ATarget* Target)
{
    Target->OnTargetDestroyed.RemoveDynamic(this, &ARhythmController::RemoveTargetFromActiveList);
    ActiveTargets.Remove(Target);

    if (IsGameFinished())
    {
        GetWorld()->GetTimerManager().SetTimer(StopGameTimer, this, &ARhythmController::OnMusicPlaybackFinished, StopGameTime, false);
    }
}

void ARhythmController::DestroyAllActiveTargets()
{
    for (ATarget* Target : ActiveTargets)
    {
        Target->DestroyTarget();
    }
}

bool ARhythmController::IsGameFinished()
{
    return bHasFinished && ActiveTargets.Num() == 0 && LastSpawnedTargetIndex == CachedTimeMap.Num();
}
