// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/AI/BossAIController.h"
#include "Boss/BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ABossAIController::ABossAIController()
{
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorThreeComponent"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABossCharacter* Boss = Cast<ABossCharacter>(InPawn);
	if (Boss && Boss->BehaviorTreeAsset)
	{
		BBC->InitializeBlackboard(*Boss->BehaviorTreeAsset->BlackboardAsset);
		BTC->StartTree(*Boss->BehaviorTreeAsset);
	}
}
