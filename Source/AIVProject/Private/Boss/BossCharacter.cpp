// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BossCharacter.h"
#include "Boss/Components/BossAttackComponent.h"
#include "Boss/Components/BossPhaseComponent.h"
#include "Enemies/BaseEnemy.h"
#include "AI/StateMachineComponent.h"
#include "Boss/AI/BossAIController.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhaseComp = CreateDefaultSubobject<UBossPhaseComponent>("PhaseComponent");
	AttackComp = CreateDefaultSubobject<UBossAttackComponent>("AttackComponent");

	//Bind c++ callbacks
	PhaseComp->OnPhaseTwo.AddDynamic(this, &ABossCharacter::SpawnReinforcements);
	PhaseComp->OnPhaseThree.AddDynamic(this, &ABossCharacter::ActivateEnrageMode);

	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossCharacter::SpawnReinforcements()
{
	FVector Base = GetActorLocation();
	for (int32 EnemyToSpawnIndex = 0; EnemyToSpawnIndex < 5; EnemyToSpawnIndex++)
	{
		FVector Offset = FVector(FMath::RandRange(-600, 600), FMath::RandRange(-600, 600), 0);
		ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(ABaseEnemy::StaticClass(), Base + Offset, FRotator::ZeroRotator);
		NewEnemy->StateMachine->ChangeState(EState::Chase);
	}
}

void ABossCharacter::ActivateEnrageMode()
{
	AttackComp->SetChargeSpeedMultiplier(3.0f);
}

