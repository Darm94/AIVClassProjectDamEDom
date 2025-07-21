// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSInteractable.h"
#include "AI/FPSComplexAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericEnemy.generated.h"

UCLASS(Abstract)
class AIVPROJECT_API AGenericEnemy : public ACharacter, public IFPSInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGenericEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Life = 100.0f;

	UFUNCTION()
	virtual void HighAlert() {};

protected:

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	virtual void UnPossessed() override;
	
	UFUNCTION()
	virtual void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	virtual void ReactToSeenActor(AActor* InActor, FVector Location) {};

	UFUNCTION()
	virtual void ReactToHeardActor(AActor* InActor, FVector Location) {};

	UFUNCTION()
	virtual void ResetHighAlert() {};

	UFUNCTION()
	virtual void OnActorDelete(AActor* ActorDestroyed);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool TriggerInteraction(AActor* InInstigator) override { return false; };

	virtual bool TriggerHit(AActor* InInstigator) override { return false; };
};
