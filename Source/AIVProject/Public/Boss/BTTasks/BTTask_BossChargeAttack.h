// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTTask_BossChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BossChargeAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
