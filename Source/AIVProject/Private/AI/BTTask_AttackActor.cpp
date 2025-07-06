// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AttackActor.h"
#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackActor::UBTTask_AttackActor()
{
}

EBTNodeResult::Type UBTTask_AttackActor::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
    //TODO:Set things to attack
    return EBTNodeResult::InProgress;
}

void UBTTask_AttackActor::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
    //TODO: Implement shoot for enemies
    //Call Shoot function
    //take into account a timer for shooting
    UBlackboardComponent* BBC = OwnerComponent.GetBlackboardComponent();
    AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!CanAttack(OwnerComponent.GetAIOwner()->GetPawn(), TargetActor))
    {
        BBC->SetValueAsBool(CanAttackKey.SelectedKeyName, false);
        FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
    }
}

bool UBTTask_AttackActor::CanAttack(APawn* ControlledPawn, AActor* TargetActor)
{
    float Distance = FVector::Distance(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
    AFPSBehaviorTreeEnemy* ThisEnemy = Cast<AFPSBehaviorTreeEnemy>(ControlledPawn);
    if (Distance >= ThisEnemy->MaxAttackRange)
    {
        return false;
    }
    return true;
}

bool UBTTask_AttackActor::ShouldFlee(APawn* ControlledPawn)
{
    return false;
}

bool UBTTask_AttackActor::ShouldCallForHelp(APawn* ControlledPawn)
{
    return false;
}
