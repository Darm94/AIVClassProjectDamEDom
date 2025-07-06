// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSInteractable.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericEnemy.generated.h"

UCLASS(Abstract)
class AIVPROJECT_API AGenericEnemy : public APawn, public IFPSInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGenericEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Life = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	virtual void HighAlert() {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

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
