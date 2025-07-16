#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HittableInterface.h"
#include "Target.generated.h"

UCLASS()
class ATarget : public AActor, public IHittableInterface
{
    GENERATED_BODY()
public:
    ATarget();

    virtual void OnHit_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void DestroyTarget();
    virtual void DestroyTarget_Implementation();

    UFUNCTION(BlueprintCallable)
    void SetImpulse(const FVector& Impulse);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
    int32 Points = 1000;
}; 