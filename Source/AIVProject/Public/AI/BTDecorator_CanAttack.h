// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTDecorator_CanAttack : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTDecorator_CanAttack();
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CanAttackKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const override;
	
};
