// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AI/StateComponent.h"
#include "FPSSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTransform PlayerTransform;

	UPROPERTY(BlueprintReadWrite)
	float PlayerLife;

	UPROPERTY(BlueprintReadWrite)
	float PlayerMaxLife;

	//UPROPERTY(BlueprintReadWrite)
	//int32 PlayerAmmo;
};

USTRUCT(BlueprintType)
struct FEnemySaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	UClass* EnemyClass;

	UPROPERTY(BlueprintReadWrite)
	FTransform EnemyTransform;

	//UPROPERTY(BlueprintReadWrite)
	//EState EnemyState;

	UPROPERTY(BlueprintReadWrite)
	float EnemyLife;
};

USTRUCT(BlueprintType)
struct FLevelSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 LevelState;

	UPROPERTY(BlueprintReadWrite)
	int32 LevelProgression;

	UPROPERTY()
	UWorld* CurrentLevel;
};

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UFPSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FPlayerSaveData PlayerSaveData;

	UPROPERTY(BlueprintReadWrite)
	TArray<FEnemySaveData> EnemiesSaveData;

	//Add timestamp to slot for Continue option and for retry.
	
};
