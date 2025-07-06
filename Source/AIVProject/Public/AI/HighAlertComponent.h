// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/StateComponent.h"
#include "HighAlertComponent.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UHighAlertComponent : public UStateComponent
{
	GENERATED_BODY()

public:

	UHighAlertComponent();

	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void PlayState() override;

	FVector TargetLocation;
	FVector AlarmOrigin;
	
};
