// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

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

	FVector PatrolLocation = BBC->GetValueAsVector("TargetPatrolLocation");

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		AIController->MoveToLocation(PatrolLocation);
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

	FVector PatrolLocation = BBC->GetValueAsVector("TargetPatrolLocation");

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
