// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/GenericEnemy.h"
#include "AI/SmartPath.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FPSBehaviorTreeEnemy.generated.h"


/**
 * 
 */
UCLASS()
class AIVPROJECT_API AFPSBehaviorTreeEnemy : public AGenericEnemy
{
	GENERATED_BODY()

public:
	AFPSBehaviorTreeEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	ASmartPath* EnemyPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float MinAttackRange = 200.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxAttackRange = 250.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float LooseChaseDistance;

	//Walk Speed Reference for animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Walkpeed = 70.0;

	//Max Speed Reference for animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxSpeed = 250.0;

	virtual void ReactToSeenActor(AActor* InActor, FVector Location) override;

	virtual void ReactToHeardActor(AActor* InActor, FVector Location) override;

protected:
	virtual void PossessedBy(AController* NewController) override;
};
