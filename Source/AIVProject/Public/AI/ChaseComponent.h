// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/StateComponent.h"
#include "ChaseComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class AIVPROJECT_API UChaseComponent : public UStateComponent
{
	GENERATED_BODY()

public:
	UChaseComponent();

	virtual void EnterState() override;
	virtual void PlayState() override;
	virtual void ExitState() override;

	inline void SetTargetActor(AActor* InActor) { TargetActor = InActor; };

private:
	AActor* TargetActor;
	
};
