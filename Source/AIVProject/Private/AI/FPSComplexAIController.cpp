// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FPSComplexAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "BehaviorTree/BehaviorTree.h"

AFPSComplexAIController::AFPSComplexAIController()
{
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehviorTreeComponent"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AFPSComplexAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AFPSBehaviorTreeEnemy* BTEnemy = Cast<AFPSBehaviorTreeEnemy>(InPawn);
	if (BTEnemy && BTEnemy->BehaviorTreeAsset)
	{
		BBC->InitializeBlackboard(*BTEnemy->BehaviorTreeAsset->BlackboardAsset);
		BTC->StartTree(*BTEnemy->BehaviorTreeAsset);
	}
}
