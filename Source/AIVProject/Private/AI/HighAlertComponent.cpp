// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HighAlertComponent.h"
#include "Enemies/BaseEnemy.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AIController.h"

UHighAlertComponent::UHighAlertComponent()
{
	StateType = EState::HighAlert;
}

void UHighAlertComponent::EnterState()
{
	// ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(GetOwner());
	// if (BaseEnemy)
	// {
	// 	BaseEnemy->SightConfig->SightRadius = BaseEnemy->SightConfig->SightRadius * BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->SightConfig->LoseSightRadius = BaseEnemy->SightConfig->LoseSightRadius * BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->HearingConfig->HearingRange = BaseEnemy->HearingConfig->HearingRange * BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->HearingConfig->LoSHearingRange = BaseEnemy->HearingConfig->LoSHearingRange * BaseEnemy->HighAlertMultiplier;
	//
	// 	//TODO: maybe increase movement speed
	//
	// 	/*float DistanceThreshold = 2000.0f;
	// 	if (FVector::Distance(AlarmOrigin, TargetLocation) < DistanceThreshold)
	// 	{
	// 		AAIController* EnemyController = Cast<AAIController>(Cast<APawn>(GetOwner())->GetController());
	// 		if (EnemyController)
	// 		{
	// 			EnemyController->MoveToLocation(TargetLocation, 200.0f);
	// 		}
	// 	}*/
	// }
}

void UHighAlertComponent::ExitState()
{
	// ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(GetOwner());
	// if (BaseEnemy)
	// {
	// 	BaseEnemy->SightConfig->SightRadius = BaseEnemy->SightConfig->SightRadius / BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->SightConfig->LoseSightRadius = BaseEnemy->SightConfig->LoseSightRadius / BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->HearingConfig->HearingRange = BaseEnemy->HearingConfig->HearingRange / BaseEnemy->HighAlertMultiplier;
	// 	BaseEnemy->HearingConfig->LoSHearingRange = BaseEnemy->HearingConfig->LoSHearingRange / BaseEnemy->HighAlertMultiplier;
	//
	// 	//TODO: maybe reduce movement speed
	// }
}

void UHighAlertComponent::PlayState()
{
}
