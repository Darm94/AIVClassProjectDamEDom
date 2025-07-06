// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BaseEnemy.h"
#include "AI/StateMachineComponent.h"
#include "AI/PatrolComponent.h"
#include "AI/ChaseComponent.h"
#include "AI/AttackComponent.h"
#include "AI/HighAlertComponent.h"
#include "FPSCharacter.h"
#include "AIController.h"
#include "Engine/TimerHandle.h"
#include "AI/EnemyAIController.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create State machine and states for ai
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>(TEXT("PatrolComponent"));
	ChaseComponent = CreateDefaultSubobject<UChaseComponent>(TEXT("ChaseComponent"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	HighAlertComponent = CreateDefaultSubobject<UHighAlertComponent>(TEXT("HighAlertComponent"));
	StateMachine = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine"));	

	AIControllerClass = AEnemyAIController::StaticClass();
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();	
}

void ABaseEnemy::ReactToSeenActor(AActor* InActor, FVector Location)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(InActor);
	if (PlayerCharacter)
	{
		StateMachine->ChangeState(EState::Chase);
	}
}

void ABaseEnemy::ReactToHeardActor(AActor* InActor, FVector Location)
{	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(Location, 100.0);
	}

}

void ABaseEnemy::HighAlert()
{
	//Double perception values
	
	if (StateMachine->GetCurrentState() == EState::HighAlert)
	{
		return;
	}

	StateMachine->ChangeState(EState::HighAlert);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	//Bind function to delegate
	TimerDelegate.BindUObject(this, &ABaseEnemy::ResetHighAlert);

	//Set {HighAlertDuration} seconds timer to call bound function when it expires
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, HighAlertDuration, false);
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ABaseEnemy::ResetHighAlert()
{
	if (StateMachine->GetCurrentState() == EState::HighAlert)
	{
		StateMachine->ChangeState(EState::Patrol);
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABaseEnemy::TriggerInteraction(AActor* InInstigator)
{
	return false;
}

bool ABaseEnemy::TriggerHit(AActor* InInstigator)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(InInstigator);
	if (PlayerCharacter)
	{
		if (StateMachine->GetCurrentState() != EState::Attack)
		{
			StateMachine->ChangeState(EState::Attack);
		}
		Life -= PlayerCharacter->ShootPotency;
		if (Life <= 0)
		{
			Destroy();
		}
		return true;
	}
	return false;
}

