// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChaseActor.h"
#include "AI/FPSComplexAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/FPSBehaviorTreeEnemy.h"

UBTTask_ChaseActor::UBTTask_ChaseActor()
{
	NodeName = "Chase Actor";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ChaseActor::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BBC = OwnerComponent.GetAIOwner()->GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(FName("TargetChaseActor")));
	//if (TargetActor)
	//{
	//}

	AAIController* EnemyController = OwnerComponent.GetAIOwner();
	EnemyController->MoveToActor(TargetActor);
	return EBTNodeResult::InProgress;
}

void UBTTask_ChaseActor::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
	AAIController* EnemyController = OwnerComponent.GetAIOwner();
	UBlackboardComponent* BBC = EnemyController->GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(FName("TargetChaseActor")));
	APawn* ControlledPawn = EnemyController->GetPawn();

	if (TargetActor)
	{
		// AGGIORNA SEMPRE LA ROTTA
		EnemyController->MoveToActor(TargetActor);
		UE_LOG(LogTemp, Warning, TEXT("Move to actor %s at Location: %s"), *TargetActor->GetName(), *TargetActor->GetActorLocation().ToString());
	}

	if (CanAttack(ControlledPawn, TargetActor))
	{
		BBC->SetValueAsBool(FName("bCanAttack"), true);
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	}

	if (ShouldFallback(ControlledPawn, TargetActor))
	{
		BBC->SetValueAsObject(FName("TargetChaseActor"), nullptr);
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
	}
}

bool UBTTask_ChaseActor::CanAttack(APawn* ControlledPawn, const AActor* TargetActor)
{
	float Distance = FVector::Distance(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
	AFPSBehaviorTreeEnemy* ThisEnemy = Cast<AFPSBehaviorTreeEnemy>(ControlledPawn);
	if(ThisEnemy)
	{
		if (Distance <= ThisEnemy->MinAttackRange)
		{
			return true;
		}
	}

	return false;
}

bool UBTTask_ChaseActor::ShouldFallback(APawn* ControlledPawn, const AActor* TargetActor)
{
	float Distance = FVector::Distance(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
	AFPSBehaviorTreeEnemy* ThisEnemy = Cast<AFPSBehaviorTreeEnemy>(ControlledPawn);
	if (ThisEnemy)
	{
		if (Distance >= ThisEnemy->LooseChaseDistance)
		{			
			return true;
		}
	}

	return false;
}
