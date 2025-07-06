// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSInteractable.h"
#include "InteractableObject.generated.h"

UCLASS()
class AIVPROJECT_API AInteractableObject : public AActor, public IFPSInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool TriggerInteraction(AActor* InInstigator) override;
	virtual bool TriggerHit(AActor* InInstigator) override;

	void TriggerBlueprintHit_Implementation(AActor* InInstigator) override;

};
