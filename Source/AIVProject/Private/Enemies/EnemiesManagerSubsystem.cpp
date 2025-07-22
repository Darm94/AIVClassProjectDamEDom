// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemiesManagerSubsystem.h"
#include "AI/StateMachineComponent.h"
#include "AI/ChaseComponent.h"
#include "Kismet/GameplayStatics.h"

void UEnemiesManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEnemiesManagerSubsystem::Deinitialize()
{
	//TODO: our things

	ActiveEnemies.Empty();

	Super::Deinitialize();
}

void UEnemiesManagerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	OnSoundAlarm.AddDynamic(this, &UEnemiesManagerSubsystem::SpawnEnemiesOnAlarm);
	OnHighAlert.AddDynamic(this, &UEnemiesManagerSubsystem::TriggerEnemiesHighAlert);
}

void UEnemiesManagerSubsystem::SpawnEnemiesOnAlarm(AActor* ActorSoundingAlarm, AActor* ActorTriggeringAlarm)
{
	TArray<ABaseEnemy*> EnemiesSpawned = SpawnBaseEnemies(10, ActorSoundingAlarm->GetActorLocation());

	for (ABaseEnemy* Enemy : EnemiesSpawned)
	{
		Enemy->StateMachine->ChangeState(EState::Chase);
		Enemy->ChaseComponent->SetTargetActor(ActorTriggeringAlarm);
	}

	UClass* BlueprintClass = LoadClass<ABaseEnemy>(nullptr, TEXT("/Game/Blueprints/BP_Sentinel.BP_Sentinel_C"));
	FVector LocationToSpawn = ActorSoundingAlarm->GetActorLocation() - ActorSoundingAlarm->GetActorForwardVector() *
		200;
	FTransform SpawnTransform(LocationToSpawn);
	ABaseEnemy* SentinelEnemy = Cast<ABaseEnemy>(SpawnEnemy(BlueprintClass, SpawnTransform));
	SentinelEnemy->StateMachine->ChangeState(EState::Chase);
}

void UEnemiesManagerSubsystem::TriggerEnemiesHighAlert(AActor* ActorSoundingAlarm, AActor* ActorTriggeringAlarm)
{
	for (AGenericEnemy* Enemy : ActiveEnemies)
	{
		Enemy->HighAlert();
	}
}

TArray<ABaseEnemy*> UEnemiesManagerSubsystem::SpawnBaseEnemies(int32 NumEnemies, FVector Location)
{
	///Script/Engine.Blueprint'/Game/Blueprints/BP_BaseEnemy.BP_BaseEnemy'

	UClass* BlueprintClass = LoadClass<ABaseEnemy>(nullptr, TEXT("/Game/Blueprints/BP_BaseEnemy.BP_BaseEnemy_C"));
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	TArray<ABaseEnemy*> SpawnedEnemies;
	for (int32 SpawnEnemiesIndex = 0; SpawnEnemiesIndex < NumEnemies; SpawnEnemiesIndex++)
	{
		//TODO: Manage location to create a point in a cer4tain radius around the spawn location
		//Create Transform based on that location
		FTransform NewEnemyTransform;
		NewEnemyTransform.SetLocation(Location);
		ABaseEnemy* NewEnemy = Cast<ABaseEnemy>(SpawnEnemy(BlueprintClass, NewEnemyTransform));
		if (NewEnemy)
		{
			SpawnedEnemies.Add(NewEnemy);
		}
	}
	return SpawnedEnemies;
}

AGenericEnemy* UEnemiesManagerSubsystem::SpawnEnemy(UClass* ClassTospawn, FTransform InTransform)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AGenericEnemy* NewEnemy = GetWorld()->SpawnActor<AGenericEnemy>(ClassTospawn, InTransform, SpawnParams);
	return NewEnemy;
}

void UEnemiesManagerSubsystem::UnregisterActiveEnemy(AGenericEnemy* EnemyToRemove)
{
	if (EnemyToRemove && ActiveEnemies.Contains(EnemyToRemove))
	{
		ActiveEnemies.Remove(EnemyToRemove);
		OnEnemyRemoved.Broadcast(EnemyToRemove);
	}
}

void UEnemiesManagerSubsystem::RegisterActiveEnemy(AGenericEnemy* EnemyToAdd)
{
	if (!EnemyToAdd || ActiveEnemies.Contains(EnemyToAdd))
	{
		return;
	}
	ActiveEnemies.Add(EnemyToAdd);
	OnEnemyAdded.Broadcast(EnemyToAdd);
}


//DECLARE DELEGATE
/*OnSomeAction.Execute();
OnSomeAction.ExecuteIfBound();*/

//int32 myint = OnDelegateRetVal.Execute();

//int32 ret = OnDelegateRetParam.Execute(5);

//OnDynamicDelegate.Execute();

//OnMulticastEvent.Broadcast();
//OnFMyMultiOneParam.Broadcast(4);
//OnMulticastDynamic.Broadcast();
