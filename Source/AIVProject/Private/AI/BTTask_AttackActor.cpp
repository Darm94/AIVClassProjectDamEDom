// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AttackActor.h"
#include "Enemies/FPSBehaviorTreeEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AttackActor::UBTTask_AttackActor()
{
    NodeName = "Attack Actor Task";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackActor::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
    //TODO:Set things to attack
    return EBTNodeResult::InProgress;
}

void UBTTask_AttackActor::TickTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaTime)
{
    UBlackboardComponent* BBC = OwnerComponent.GetBlackboardComponent();
    AActor* TargetActor = Cast<AActor>(BBC->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!CanAttack(OwnerComponent.GetAIOwner()->GetPawn(), TargetActor))
    {
        BBC->SetValueAsBool(CanAttackKey.SelectedKeyName, false);
        FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
    }

    // Chosen Damage
    float DamageAmount = 10.0f;

    // 1) Call Interface
    IFPSInteractable* Interactable = Cast<IFPSInteractable>(TargetActor);
    if (Interactable)
    {
        Interactable->TriggerHit(OwnerComponent.GetAIOwner()->GetPawn());
    }else
    {
        // 2) ApplyDamage
        UGameplayStatics::ApplyDamage(
            TargetActor,
            DamageAmount,
            OwnerComponent.GetAIOwner(),  // InstigatorController
            OwnerComponent.GetAIOwner()->GetPawn(), // DamageCauser
            UDamageType::StaticClass()
        );
    }
    // 3) Finish the task, the attack condition have to be checked again
    FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
   
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
