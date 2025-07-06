// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BTServices/BTService_UpdateAmmo.h"
#include "Boss/BossCharacter.h"
#include "Boss/Components/BossAttackComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateAmmo::UBTService_UpdateAmmo()
{
	NodeName = TEXT("Update Ammo");
}

void UBTService_UpdateAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ABossCharacter* Boss = Cast<ABossCharacter>(AIController->GetPawn()))
		{
			if (UBossAttackComponent* AttackComp = Boss->GetComponentByClass<UBossAttackComponent>())
			{
				UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
				BBC->SetValueAsInt(CurrentAmmoKey.SelectedKeyName, AttackComp->CurrentAmmo);
			}
		}
	}
}
