// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSObjective.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UFPSObjective : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KeyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KilledEnemies;

	UPROPERTY()
	int KilledEnemiesCount;
	
	UPROPERTY()
	int EnemiesCount;

public:
	UFUNCTION(BlueprintCallable)
	void SetHasKey(bool bHasKey);

	UFUNCTION(BlueprintCallable)
	void AddKill();

	UFUNCTION(BlueprintCallable)
	void AddEnemy();

private:
	UFUNCTION(BlueprintCallable)
	void SetKilledEnemies(int Killed, int MaxEnemies);
};
