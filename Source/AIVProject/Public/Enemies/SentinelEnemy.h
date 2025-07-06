// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/BaseEnemy.h"
#include "SentinelEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API ASentinelEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ASentinelEnemy();

	virtual void ReactToSeenActor(AActor* InActor, FVector Location) override;
	virtual void ReactToHeardActor(AActor* InActor, FVector Location) override;
	
};
