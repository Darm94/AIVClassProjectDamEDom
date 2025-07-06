// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPointOnPath.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UBTTask_GetPointOnPath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetPointOnPath();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

protected:
	int32 PointIndex = 0;
	
};
