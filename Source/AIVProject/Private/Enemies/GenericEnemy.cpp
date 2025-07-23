// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GenericEnemy.h"

#include "FPSCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemies/EnemiesManagerSubsystem.h"

AGenericEnemy::AGenericEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGenericEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
	EnemiesManager->RegisterActiveEnemy(this);
	OnDestroyed.AddDynamic(this, &AGenericEnemy::OnActorDelete);
}

//Register ComplexController AiPerception Delegate for perception updated
void AGenericEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AFPSComplexAIController* AIController = Cast<AFPSComplexAIController>(NewController))
	{
		AIPerceptionComponent = AIController->AIPerceptionComponent;
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AGenericEnemy::PerceptionUpdated);
	}
}

//Clean ComplexController AiPerception Delegate
void AGenericEnemy::UnPossessed()
{
	Super::UnPossessed();
	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnPerceptionUpdated.RemoveAll(this);
		AIPerceptionComponent = nullptr;
	}
}

void AGenericEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGenericEnemy::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo Info;
		if (AIPerceptionComponent)
		{
			AIPerceptionComponent->GetActorsPerception(Actor, Info);
			if (Info.LastSensedStimuli.Num() > 0)
			{
				for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
				{
					if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>() && Stimulus.WasSuccessfullySensed())
					{
						//UE_LOG(LogTemp, Warning, TEXT("Saw actor %s at Location: %s"), *Actor->GetName(),
						//       *Stimulus.StimulusLocation.ToString());
						ReactToSeenActor(Actor, Stimulus.StimulusLocation);
					}
					else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>() && Stimulus.
						WasSuccessfullySensed())
					{
						//UE_LOG(LogTemp, Warning, TEXT("Heard actor %s at Location: %s"), *Actor->GetName(),
						//       *Stimulus.StimulusLocation.ToString());
						ReactToHeardActor(Actor, Stimulus.StimulusLocation);
					}
				}
			}
		}
	}
}

void AGenericEnemy::OnActorDelete(AActor* ActorDestroyed)
{
	UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
	EnemiesManager->UnregisterActiveEnemy(this);
}

// Called to bind functionality to input
void AGenericEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


float AGenericEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Take damage"));
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Life -= DamageAmount;
	/*if (Life <= 0)
	{
		Destroy();
	}*/

	if (Life <= 0 && !bIsDying) // avoiding double call
	{
		bIsDying = true;

		// Disable collisions
		SetActorEnableCollision(false);

		// block movement
		if (auto* MoveComp = GetCharacterMovement())
		{
			MoveComp->DisableMovement();
		}

		// play death montage
		if (DeathMontage && GetMesh())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
		}

		// destroy after 5 seconds
		FTimerHandle DestroyTimerHandle;
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AGenericEnemy::DelayedDestroy, 2.3f, false);
	}

	return DamageAmount;
}

void AGenericEnemy::DelayedDestroy()
{
	Destroy();
}