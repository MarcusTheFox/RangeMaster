#include "Actors/RhythmController.h"

#include "Components/AudioComponent.h"
#include "FunctionLibraries/BeatMapFunctionLibrary.h"
#include "Sound/SoundWaveProcedural.h"

ARhythmController::ARhythmController()
{
    PrimaryActorTick.bCanEverTick = false;

    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->SetupAttachment(RootComponent);
    MusicComponent->bAutoActivate = false;
}

void ARhythmController::BeginPlay()
{
    Super::BeginPlay();
    if (MusicComponent)
    {
        MusicComponent->OnAudioPlaybackPercent.AddDynamic(this, &ARhythmController::HandleMusicPlaybackPercent);
        MusicComponent->OnAudioFinished.AddDynamic(this, &ARhythmController::HandleMusicPlaybackFinished);
    }
}

void ARhythmController::PrepareTrack(USoundWave* SoundWave, const TArray<FTimeMapData>& TimeMap)
{
    CurrentSoundWave = SoundWave;
    CachedTimeMap = TimeMap;
    MusicComponent->SetSound(CurrentSoundWave);
    
    bIsReadyToPlay = true;
    OnReadyToPlay.Broadcast();
}

void ARhythmController::Play()
{
    if (MusicComponent)
    {
        NextBeatIndex = 0;
        bIsPlaying = true;
        bIsReadyToPlay = false;
        MusicComponent->Play();
    }
}

void ARhythmController::Stop()
{
    if (MusicComponent)
    {
        MusicComponent->Stop();
        MusicComponent->SetSound(nullptr);
        CurrentSoundWave = nullptr;
    }
    bIsPlaying = false;
    bIsReadyToPlay = false;
}

void ARhythmController::ResetMusic(USoundWave* SoundWave)
{
    PrepareTrack(SoundWave, CachedTimeMap);
}

void ARhythmController::HandleMusicPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent)
{
    if (!bIsPlaying || !CurrentSoundWave || PlayingSoundWave != CurrentSoundWave) return;

    if (CurrentSoundWave->IsA<USoundWaveProcedural>())
    {
        if (PlaybackPercent >= 1.0f)
        {
            MusicComponent->Stop();
            return;
        }
    }

    const float CurrentTime = PlaybackPercent * PlayingSoundWave->Duration;
    CheckBeatAtTime(CurrentTime);
}

void ARhythmController::HandleMusicPlaybackFinished()
{
    if (!bIsPlaying) return;
    
    bIsPlaying = false;
    
    OnMusicFinished.Broadcast();
}

void ARhythmController::CheckBeatAtTime(float CurrentTime)
{
    if (CachedTimeMap.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CachedTimeMap is empty!"));
        return;
    }
    
    while (NextBeatIndex < CachedTimeMap.Num())
    {
        const FTimeMapData& Data = CachedTimeMap[NextBeatIndex];
        if (Data.Time > CurrentTime) break;
        
        if (Data.ShotPower > 0)
        {
            OnBeat.Broadcast(Data);
        }
        NextBeatIndex++;
    }
}
