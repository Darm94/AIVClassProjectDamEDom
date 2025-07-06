// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ChaseComponent.h"

UChaseComponent::UChaseComponent()
{
	StateType = EState::Chase;
}

void UChaseComponent::EnterState()
{
	//GetPlayerController->GetPawn
	//Set target
}

void UChaseComponent::PlayState()
{
}

void UChaseComponent::ExitState()
{
}
