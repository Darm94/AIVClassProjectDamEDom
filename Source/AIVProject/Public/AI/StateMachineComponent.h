// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.h"
#include "StateMachineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class AIVPROJECT_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateMachineComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EState InitialState = EState::Patrol;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(EState NextState);

	virtual void OnRegister() override;

	inline EState GetCurrentState() { return CurrentState; };


private:
	EState CurrentState;
	TMap<EState, UStateComponent*> OwnerAvailableStateComponenets;		
	void RegisterState(EState StateType, UStateComponent* State);
};
