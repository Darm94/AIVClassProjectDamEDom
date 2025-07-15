// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "AI/StateMachineComponent.h"
#include "AI/FPSComplexAIController.h"
#include "FPSCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AFPSBehaviorTreeEnemy::AFPSBehaviorTreeEnemy()
{
	AIControllerClass = AFPSComplexAIController::StaticClass();

	LooseChaseDistance = SightConfig->SightRadius * 1.5;
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

}


void AFPSBehaviorTreeEnemy::ReactToSeenActor(AActor* InActor, FVector Location)
{
	if(InActor)
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(InActor);
		AFPSComplexAIController* EnemyController = Cast<AFPSComplexAIController>(GetController());
		if (Player && EnemyController)
		{
			EnemyController->BBC->SetValueAsObject(FName("TargetChaseActor"),InActor);
		}
	}
}

void AFPSBehaviorTreeEnemy::ReactToHeardActor(AActor* InActor, FVector Location)
{
	if(InActor)
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(InActor);
		AFPSComplexAIController* EnemyController = Cast<AFPSComplexAIController>(GetController());
		if (Player && EnemyController)
		{
			EnemyController->BBC->SetValueAsObject(FName("TargetChaseActor"),InActor);
		}
	}
}
