// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BTServices/BTService_UpdateHealth.h"
#include "AIController.h"
#include "Boss/BossCharacter.h"
#include "Boss/Components/BossPhaseComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateHealth::UBTService_UpdateHealth()
{
	NodeName = TEXT("Update Health & Phase");
	
	HealthPercentKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateHealth, HealthPercentKey));
	CurrentPhaseKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateHealth, CurrentPhaseKey));
}

void UBTService_UpdateHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (ABossCharacter* Boss = Cast<ABossCharacter>(Pawn))
		{
			if (UBossPhaseComponent* PhaseComp = Boss->FindComponentByClass<UBossPhaseComponent>())
			{
				const float HealtPercentage = PhaseComp->CurrentHealth / PhaseComp->MaxHealth;
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(HealthPercentKey.SelectedKeyName, HealtPercentage);
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(CurrentPhaseKey.SelectedKeyName, PhaseComp->CurrentPhase);
			}
		}
	}
}
