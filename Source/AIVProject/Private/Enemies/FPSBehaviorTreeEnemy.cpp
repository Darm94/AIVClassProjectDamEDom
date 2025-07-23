// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "AI/FPSComplexAIController.h"
#include "FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AFPSBehaviorTreeEnemy::AFPSBehaviorTreeEnemy()
{
	AIControllerClass = AFPSComplexAIController::StaticClass();
}


void AFPSBehaviorTreeEnemy::ReactToSeenActor(AActor* InActor, FVector Location)
{
	if (InActor)
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(InActor);
		AFPSComplexAIController* EnemyController = Cast<AFPSComplexAIController>(GetController());
		if (Player && EnemyController)
		{
			EnemyController->BBC->SetValueAsObject(FName("TargetChaseActor"), InActor);
		}
	}
}

void AFPSBehaviorTreeEnemy::ReactToHeardActor(AActor* InActor, FVector Location)
{
	if (InActor)
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(InActor);
		AFPSComplexAIController* EnemyController = Cast<AFPSComplexAIController>(GetController());
		if (Player && EnemyController)
		{
			EnemyController->BBC->SetValueAsVector(FName("TargetPatrolLocation"), Location);
			EnemyController->MoveToLocation(Location);
			GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
		}
	}
}

// Set LooseChaseDistance based on ComplexController SightConfig
void AFPSBehaviorTreeEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AFPSComplexAIController* ComplexController = Cast<AFPSComplexAIController>(NewController))
	{
		LooseChaseDistance = ComplexController->SightConfig->SightRadius * 1.5;
	}
}
