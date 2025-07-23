// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FPSComplexAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AFPSComplexAIController::AFPSComplexAIController()
{
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehviorTreeComponent"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	////////////////////////////////////////////////////////////
	// //////////////////AI/////////////////////////////////////
	// /////////////////////////////////////////////////////////
	//Create AI perception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	FAISenseAffiliationFilter AffiliationFilter;
	AffiliationFilter.bDetectEnemies = true;
	AffiliationFilter.bDetectFriendlies = false;
	AffiliationFilter.bDetectNeutrals = false;
	
	//Create and configure senses
	//Create Sight
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIPerceptionSight"));
	
	//Configure sight
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation = AffiliationFilter;

	//create hearing
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AIPerceptionHearing"));
	
	//configure hearing
	HearingConfig->HearingRange = 2000.0;
	HearingConfig->SetMaxAge(5.0);
	HearingConfig->DetectionByAffiliation = AffiliationFilter;
	
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	/////////////////////////////////////////////////////////////
	/////////////////////END AI//////////////////////////////////
	/////////////////////////////////////////////////////////////

}

void AFPSComplexAIController::OnPossess(APawn* InPawn)
{
	SetGenericTeamId(FGenericTeamId(1));
	Super::OnPossess(InPawn);
	AFPSBehaviorTreeEnemy* BTEnemy = Cast<AFPSBehaviorTreeEnemy>(InPawn);
	if (BTEnemy && BTEnemy->BehaviorTreeAsset)
	{
		BBC->InitializeBlackboard(*BTEnemy->BehaviorTreeAsset->BlackboardAsset);
		BTC->StartTree(*BTEnemy->BehaviorTreeAsset);
	}
}

ETeamAttitude::Type AFPSComplexAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();
		if (OtherTeamId == FGenericTeamId::NoTeam)
		{
			return ETeamAttitude::Neutral;
		}

		if (OtherTeamId == GetGenericTeamId())
		{
			return ETeamAttitude::Friendly;
		}
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Neutral;
}
