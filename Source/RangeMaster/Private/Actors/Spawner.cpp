#include "Actors/Spawner.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "RangeMasterGameMode.h"
#include "HitType.h"
#include "FunctionLibraries/GameUtilityFunctionLibrary.h"

ASpawner::ASpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    OverlapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OverlapComponent"));
    OverlapComponent->SetupAttachment(SceneRoot);
    OverlapComponent->SetCollisionProfileName(TEXT("TargetSpawner"));
    OverlapComponent->SetGenerateOverlapEvents(true);
}

void ASpawner::BeginPlay()
{
    Super::BeginPlay();
    if (OverlapComponent)
    {
        OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawner::OnOverlapBegin);
    }
}

void ASpawner::SpawnTarget_Implementation(TSubclassOf<ATarget> TargetClass, int32 Power)
{
    if (!TargetClass) return;
    UWorld* World = GetWorld();
    if (!World) return;

    FTransform SpawnTransform = GetActorTransform();
    FVector SpawnLocation = SpawnTransform.GetLocation() + SpawnOffset;
    SpawnTransform.SetLocation(SpawnLocation);

    ATarget* Target = World->SpawnActor<ATarget>(TargetClass, SpawnTransform);
    if (Target)
    {
        FVector Impulse = FVector::UpVector * Power;
        Target->SetImpulse(Impulse);
    }
}

void ASpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                              bool bFromSweep, const FHitResult& SweepResult)
{
    if (ATarget* Target = Cast<ATarget>(OtherActor))
    {
        Target->DestroyTarget();
        ARangeMasterGameMode* GM = UGameUtilityFunctionLibrary::GetRangeMasterGameMode(this);
        if (GM)
        {
            GM->RegisterHit(EHitType::Miss);
            if (GM->ScoreSystem)
            {
                GM->ScoreSystem->ResetCombo();
            }
        }
    }
} 