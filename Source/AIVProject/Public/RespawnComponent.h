#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIVPROJECT_API URespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URespawnComponent();

protected:
    virtual void BeginPlay() override;

public:
    // where respawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
    FVector RespawnLocation = FVector(3236.45f, -220.0f, 220.0f);

    UFUNCTION(BlueprintCallable)
    void RespawnPlayer();
};
