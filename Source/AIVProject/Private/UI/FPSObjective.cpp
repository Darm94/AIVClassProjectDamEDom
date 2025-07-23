// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPSObjective.h"

#include "Components/TextBlock.h"

void UFPSObjective::SetKilledEnemies(int Killed, int MaxEnemies)
{
	KilledEnemies->SetText(FText::FromString(
		FString::Printf(TEXT("%d / %d"), Killed, MaxEnemies)
	));
}

void UFPSObjective::SetHasKey(bool bHasKey)
{
	KeyText->SetText(FText::FromString(bHasKey ? "Key Found" : "Key Not Found"));
}

void UFPSObjective::AddKill()
{
	KilledEnemiesCount++;
	SetKilledEnemies(KilledEnemiesCount, EnemiesCount);
}

void UFPSObjective::AddEnemy()
{
	EnemiesCount++;
	SetKilledEnemies(KilledEnemiesCount, EnemiesCount);
}
