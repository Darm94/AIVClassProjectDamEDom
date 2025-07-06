// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/StateComponent.h"
#include "AttackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class AIVPROJECT_API UAttackComponent : public UStateComponent
{
	GENERATED_BODY()

public:
	UAttackComponent();

	virtual void EnterState() override;
	virtual void PlayState() override;
	virtual void ExitState() override;
	
};
