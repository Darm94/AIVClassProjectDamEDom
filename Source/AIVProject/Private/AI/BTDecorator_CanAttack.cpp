// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanAttack.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	bool bCanAttack = BBC->GetValueAsBool(CanAttackKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (bCanAttack && TargetActor)
	{
		return true;
	}
	return false;
}
