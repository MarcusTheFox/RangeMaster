#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HittableInterface.generated.h"

UINTERFACE(BlueprintType)
class UHittableInterface : public UInterface
{
    GENERATED_BODY()
};

class IHittableInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Hit")
    void OnHit();
}; 