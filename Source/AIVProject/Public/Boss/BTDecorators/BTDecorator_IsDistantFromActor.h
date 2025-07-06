// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsDistantFromActor.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTDecorator_IsDistantFromActor : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsDistantFromActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Condition", meta = (ClampMin = "0.0"))
	float DistanceThreshold;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
