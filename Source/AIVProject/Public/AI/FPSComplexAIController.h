// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSComplexAIController.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API AFPSComplexAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFPSComplexAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class UBehaviorTreeComponent* BTC;

	UPROPERTY()
	class UBlackboardComponent* BBC;

	//FBlackboard::FKey 
	
};
