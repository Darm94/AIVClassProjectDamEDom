// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChaseActor.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTTask_ChaseActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ChaseActor();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime) override;

private:
	bool CanAttack(APawn* ControlledPawn, const AActor* TargetActor);
	bool ShouldFallback(APawn* ControlledPawn, const AActor* TargetActor);
};
