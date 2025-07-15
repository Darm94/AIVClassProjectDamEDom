// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include <Enemies/FPSBehaviorTreeEnemy.h>

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	
	UBlackboardComponent* BBC = OwnerComponent.GetBlackboardComponent();
	if (!AIController || !BBC)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	//Take Enemy class and stats
	AFPSBehaviorTreeEnemy* ThisEnemy = Cast<AFPSBehaviorTreeEnemy>(ControlledPawn);
	FVector PatrolLocation = BBC->GetValueAsVector("TargetPatrolLocation");
	if (PatrolLocation.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Patrol Execute] Fallback: PatrolLocation is ZERO — failing!"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		/*
		if (ThisEnemy && ThisEnemy->FloatingPawnMovement)
		{
			ThisEnemy->FloatingPawnMovement->MaxSpeed = ThisEnemy->Walkpeed;
		}
		AIController->MoveToLocation(PatrolLocation);
		*/
		if (ThisEnemy && ThisEnemy->FloatingPawnMovement)
		{
			ThisEnemy->FloatingPawnMovement->MaxSpeed = ThisEnemy->Walkpeed;
			ThisEnemy->FloatingPawnMovement->Acceleration = 99999.f;   
			ThisEnemy->FloatingPawnMovement->Deceleration = 99999.f;   
		}
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComponent, NodeMemory, DeltaTime);

	

	AAIController* AIController = OwnerComponent.GetAIOwner();
	UBlackboardComponent* BBC = OwnerComponent.GetBlackboardComponent();
	if (!AIController || !BBC)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
	}

	FVector Velocity = ControlledPawn->GetVelocity();
	Velocity.Z = 0;
	if (!Velocity.IsNearlyZero())
	{
		FRotator NewRotation = Velocity.Rotation();
		ControlledPawn->SetActorRotation(NewRotation);
	}

	FVector PatrolLocation = BBC->GetValueAsVector("TargetPatrolLocation");
	//Fallback if TargetPatrolLocation is 0
	if (PatrolLocation.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Patrol Tick] Fallback: PatrolLocation is ZERO — forcing next point!"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return;
	}

	// Fallback from chase
	if (HasReachedTarget(ControlledPawn, PatrolLocation, 50))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Patrol Tick] Fallback: Already at patrol point — forcing next!"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return;
	}
	//Tick Movement
	FVector Direction = (PatrolLocation - ControlledPawn->GetActorLocation()).GetSafeNormal();

	UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());

	if (!Direction.IsNearlyZero())
	{
		ControlledPawn->AddMovementInput(Direction, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("AddMovementInput CALLED"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Direction is ZERO — NO INPUT"));
	}

	if (HasReachedTarget(ControlledPawn, PatrolLocation, 200))
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	}
	AActor* TargetChaseActor = Cast<AActor>(BBC->GetValueAsObject("TargetChaseActor"));
	if (TargetChaseActor)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	}

}

bool UBTTask_Patrol::HasReachedTarget(const APawn* ControlledPawn, const FVector& TargetLocation, float AcceptanceRadius)
{
	FVector ControlledPawnLocation = ControlledPawn->GetActorLocation();
	return FVector::Distance(ControlledPawnLocation, TargetLocation) < AcceptanceRadius;
}
