// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();	

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
