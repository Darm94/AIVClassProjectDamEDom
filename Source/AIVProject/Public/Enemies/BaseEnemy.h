// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/GenericEnemy.h"
#include "BaseEnemy.generated.h"

UCLASS()
class AIVPROJECT_API ABaseEnemy : public AGenericEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AI")
	class UStateMachineComponent* StateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UPatrolComponent* PatrolComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UChaseComponent* ChaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAttackComponent* AttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UHighAlertComponent* HighAlertComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Alert")
	float HighAlertMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Alert")
	float HighAlertDuration = 20.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool TriggerInteraction(AActor* InInstigator) override;

	virtual bool TriggerHit(AActor* InInstigator) override;

	virtual void HighAlert() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ResetHighAlert() override;

	virtual void ReactToSeenActor(AActor* InActor, FVector Location) override;

	virtual void ReactToHeardActor(AActor* InActor, FVector Location) override;
};
