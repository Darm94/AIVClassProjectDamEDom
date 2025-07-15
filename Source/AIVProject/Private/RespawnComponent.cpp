#include "RespawnComponent.h"
#include "GameFramework/Actor.h"

URespawnComponent::URespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // Non serve tick continuo
}

void URespawnComponent::BeginPlay()
{
    Super::BeginPlay();
}

void URespawnComponent::RespawnPlayer()
{
    if (AActor* Owner = GetOwner())
    {
        Owner->SetActorLocation(RespawnLocation);
        UE_LOG(LogTemp, Warning, TEXT("Player respawned at %s"), *RespawnLocation.ToString());
    }
}