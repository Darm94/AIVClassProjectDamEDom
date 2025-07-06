// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackActor.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTTask_AttackActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AttackActor();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CanAttackKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime) override;

private:
	bool CanAttack(APawn* ControlledPawn, AActor* TargetActor);
	bool ShouldFlee(APawn* ControlledPawn);
	bool ShouldCallForHelp(APawn* ControlledPawn);
	
};
