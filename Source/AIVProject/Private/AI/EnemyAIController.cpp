// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"
#include "GenericTeamAgentInterface.h"

AEnemyAIController::AEnemyAIController()
{
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();
		if (OtherTeamId == FGenericTeamId::NoTeam)
		{
			return ETeamAttitude::Neutral;
		}
		else if (OtherTeamId == GetGenericTeamId())
		{
			return ETeamAttitude::Friendly;
		}
		else
		{
			return ETeamAttitude::Hostile;
		}
	}
	else
	{
		return ETeamAttitude::Neutral;
	}
}
