// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateMachineComponent.h"

// Sets default values for this component's properties
UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	TSet<UActorComponent*> OwnerComponents;
	OwnerComponents = GetOwner()->GetComponents();
	for (UActorComponent* Component : OwnerComponents)
	{
		UStateComponent* StateComponent = Cast<UStateComponent>(Component);
		if (StateComponent)
		{
			RegisterState(StateComponent->StateType, StateComponent);
		}
	}

	CurrentState = InitialState;
	if (OwnerAvailableStateComponenets.Contains(CurrentState))
	{
		OwnerAvailableStateComponenets[CurrentState]->EnterState();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tring to start a StateMachine on Actor: %s with a State that is not available to the actor. Please fix it to avoid other issues in AI behaviour."), *GetOwner()->GetName());
	}

	// ...
	
}


// Called every frame
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwnerAvailableStateComponenets.Contains(CurrentState))
	{
		OwnerAvailableStateComponenets[CurrentState]->PlayState();
	}
}

void UStateMachineComponent::ChangeState(EState NextState)
{
	if (OwnerAvailableStateComponenets.Contains(NextState))
	{
		OwnerAvailableStateComponenets[CurrentState]->ExitState();
		CurrentState = NextState;
		OwnerAvailableStateComponenets[CurrentState]->EnterState();
	}
	/*else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to change to an unavailable state on Actor: %s"), *GetOwner()->GetName());
	}*/
}

void UStateMachineComponent::OnRegister()
{
	Super::OnRegister();

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("State Machine Component can only be attached to Pawn actors and derivates"));
		UnregisterComponent();
	}
}

void UStateMachineComponent::RegisterState(EState StateType, UStateComponent* State)
{
	OwnerAvailableStateComponenets.Add(StateType, State);
}

