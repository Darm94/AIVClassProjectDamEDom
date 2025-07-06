// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BTDecorators/BTDecorator_IsDistantFromActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTDecorator_IsDistantFromActor::UBTDecorator_IsDistantFromActor()
{
	NodeName = TEXT("Distance > Threshold");
}

bool UBTDecorator_IsDistantFromActor::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (!BBC)
	{
		return false;
	}

	AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(TargetActorKey.SelectedKeyName));
	//APawn* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			if (TargetActor)
			{
				const float Distance = ControlledPawn->GetDistanceTo(TargetActor);
				return Distance > DistanceThreshold;
			}
		}
	}
	return false;
}