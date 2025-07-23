// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FloatingComponent.h"

// Sets default values for this component's properties
UFloatingComponent::UFloatingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingComponent::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UFloatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner()) return;

	RunningTime += DeltaTime;

	FVector NewLocation = InitialLocation;
	NewLocation.Z += FMath::Sin(RunningTime * Frequency) * Amplitude;

	GetOwner()->SetActorLocation(NewLocation);
	// ...
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw += RotationSpeed * DeltaTime;
	GetOwner()->SetActorRotation(CurrentRotation);
}

