// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractableObject::TriggerInteraction(AActor* InInstigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Successfully interacted with: %s"), *GetName());
	return true;
}

bool AInteractableObject::TriggerHit(AActor* InInstigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Successfully shot: %s"), *GetName());
	return true;
}

void AInteractableObject::TriggerBlueprintHit_Implementation(AActor* InInstigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Successfully triggered hit implementation in cpp"));
}

