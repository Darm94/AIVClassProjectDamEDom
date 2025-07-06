// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EState : uint8
{
	Patrol,
	Chase,
	Attack,
	HighAlert
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable )
class AIVPROJECT_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateComponent();

	EState StateType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void EnterState() {};

	UFUNCTION(BlueprintCallable)
	virtual void ExitState() {};

	UFUNCTION(BlueprintCallable)
	virtual void PlayState() {};		
};
