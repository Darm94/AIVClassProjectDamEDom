// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataManager.h"
#include "Data/FPSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.h"
#include "Enemies/EnemiesManagerSubsystem.h"
#include "Enemies/BaseEnemy.h"
#include "AI/StateMachineComponent.h"

void UDataManager::SaveGame(const FString& SlotName, int32 UserIndex)
{
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UFPSSaveGame::StaticClass());
	UFPSSaveGame* FPSSaveGame = Cast<UFPSSaveGame>(SaveGame);
	if (FPSSaveGame)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			AFPSCharacter* FPSPlayer = Cast<AFPSCharacter>(PlayerCharacter);
			if (FPSPlayer)
			{
				FPSSaveGame->PlayerSaveData.PlayerTransform = FPSPlayer->GetActorTransform();
				FPSSaveGame->PlayerSaveData.PlayerLife = FPSPlayer->CurrentHealth;
				FPSSaveGame->PlayerSaveData.PlayerMaxLife = FPSPlayer->MaxHealth;
			}

			UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
			for (AGenericEnemy* Enemy : EnemiesManager->GetActiveEnemies())
			{
				FEnemySaveData EnemySaveData;
				EnemySaveData.EnemyClass = Enemy->StaticClass();
				EnemySaveData.EnemyTransform = Enemy->GetActorTransform();
				//EnemySaveData.EnemyState = Enemy->StateMachine->GetCurrentState();
				EnemySaveData.EnemyLife = Enemy->Life;

				FPSSaveGame->EnemiesSaveData.Add(EnemySaveData);
			}

			UGameplayStatics::SaveGameToSlot(FPSSaveGame, SlotName, UserIndex);
		}
	}
}

void UDataManager::LoadGame(const FString& SlotName, int32 UserIndex)
{
	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
	UFPSSaveGame* FPSSaveGame = Cast<UFPSSaveGame>(SaveGame);

	if (FPSSaveGame)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			PlayerCharacter->SetActorTransform(FPSSaveGame->PlayerSaveData.PlayerTransform);
			AFPSCharacter* FPSPlayer = Cast<AFPSCharacter>(PlayerCharacter);
			if (FPSPlayer)
			{
				FPSPlayer->CurrentHealth = FPSSaveGame->PlayerSaveData.PlayerLife;
				FPSPlayer->MaxHealth = FPSSaveGame->PlayerSaveData.PlayerMaxLife;
			}
		}

		UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
		for (AGenericEnemy* Enemy : EnemiesManager->GetActiveEnemies())
		{
			Enemy->Destroy();
		}

		for (FEnemySaveData EnemySaveData : FPSSaveGame->EnemiesSaveData)
		{
			AGenericEnemy* SpawnedEnemy = EnemiesManager->SpawnEnemy(EnemySaveData.EnemyClass, EnemySaveData.EnemyTransform);
			SpawnedEnemy->Life = EnemySaveData.EnemyLife;
			//SpawnedEnemy->StateMachine->ChangeState(EnemySaveData.EnemyState);
		}
	}
}
