// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/SentinelEnemy.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "FPSCharacter.h"
#include "AI/StateMachineComponent.h"
#include "Enemies/EnemiesManagerSubsystem.h"

ASentinelEnemy::ASentinelEnemy()
{
	SightConfig->SightRadius = 2000.0f;
	SightConfig->LoseSightRadius = 2500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 100.0f;
	SightConfig->SetMaxAge(5.0f);

	HearingConfig->HearingRange = 1200.0;
	HearingConfig->LoSHearingRange = 2000.0;
	HearingConfig->bUseLoSHearing = true;
	HearingConfig->SetMaxAge(5.0);
}

void ASentinelEnemy::ReactToSeenActor(AActor* InActor, FVector Location)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(InActor);
	if (PlayerCharacter)
	{
		//TODO: Send alarm to spawn other enemies towards the player. (Could also lock doors, change lightning etc...)
		UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
		
		//EnemiesManager->SpawnBaseEnemies(5, GetActorLocation());
		
		if (StateMachine->GetCurrentState() == EState::Patrol)
		{
			EnemiesManager->OnSoundAlarm.Broadcast(this, PlayerCharacter);
			StateMachine->ChangeState(EState::Chase);
		}
	}
	//Super::ReactToSeenActor(InActor, Location);
}

void ASentinelEnemy::ReactToHeardActor(AActor* InActor, FVector Location)
{
	UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
	EnemiesManager->OnHighAlert.Broadcast(this, InActor);
	//TODO send signal to put other enemies on high alert for an amount of time
	Super::ReactToHeardActor(InActor, Location);
}


