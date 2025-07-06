// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BTTasks/BTTask_BossChargeAttack.h"
#include "Boss/BossCharacter.h"
#include "Boss/Components/BossAttackComponent.h"
#include "AIController.h"

UBTTask_BossChargeAttack::UBTTask_BossChargeAttack()
{
	NodeName = TEXT("Boss Charge Attack");
}

EBTNodeResult::Type UBTTask_BossChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ABossCharacter* Boss = Cast<ABossCharacter>(AIController->GetPawn()))
		{
			if (UBossAttackComponent* AttackComp = Boss->FindComponentByClass<UBossAttackComponent>())
			{
				AttackComp->PerformCharge();
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
