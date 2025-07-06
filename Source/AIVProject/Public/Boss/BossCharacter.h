// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

class UBossPhaseComponent;
class UBossAttackComponent;
class UBehaviorTree;

UCLASS()
class AIVPROJECT_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBossPhaseComponent* PhaseComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBossAttackComponent* AttackComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	float ArmorValue = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	float FireResistance = 0.25f;

	UFUNCTION()
	void SpawnReinforcements();

	UFUNCTION()
	void ActivateEnrageMode();

};
