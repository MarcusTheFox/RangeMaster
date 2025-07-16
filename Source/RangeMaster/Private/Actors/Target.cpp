#include "Actors/Target.h"
#include "GameFunctionLibrary.h"
#include "RangeMasterGameMode.h"
#include "ScoreSystemComponent.h"
#include "Components/PrimitiveComponent.h"

ATarget::ATarget()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATarget::OnHit_Implementation()
{
    ARangeMasterGameMode* GM = UGameFunctionLibrary::GetRangeMasterGameMode(this);
    if (GM && GM->ScoreSystem)
    {
        GM->ScoreSystem->IncreaseCombo();
        GM->ScoreSystem->AddScore(Points * GM->ScoreSystem->GetComboMultiplier());
    }
    if (GM)
    {
        GM->RegisterHit(EHitType::Perfect);
    }
    DestroyTarget();
}

void ATarget::DestroyTarget_Implementation()
{
    Destroy();
}

void ATarget::SetImpulse(const FVector& Impulse)
{
    if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent()))
    {
        Prim->AddImpulse(Impulse, NAME_None, true);
    }
} 