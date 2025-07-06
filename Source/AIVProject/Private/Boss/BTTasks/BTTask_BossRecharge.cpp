// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BTTasks/BTTask_BossRecharge.h"
#include "Boss/BossCharacter.h"
#include "Boss/Components/BossAttackComponent.h"
#include "AIController.h"

UBTTask_BossRecharge::UBTTask_BossRecharge()
{
	NodeName = TEXT("Recharge Ammo");
}

EBTNodeResult::Type UBTTask_BossRecharge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ABossCharacter* Boss = Cast<ABossCharacter>(AIController->GetPawn()))
		{
			if (UBossAttackComponent* AttackComp = Boss->GetComponentByClass<UBossAttackComponent>())
			{
				AttackComp->CurrentAmmo = AttackComp->MaxAmmo;
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
