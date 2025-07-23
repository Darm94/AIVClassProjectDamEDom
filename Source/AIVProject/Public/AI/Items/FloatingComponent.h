// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIVPROJECT_API UFloatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating")
	float Amplitude = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating")
	float Frequency = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating")
	float RotationSpeed = 30.f;

private:
	FVector InitialLocation;
	float RunningTime = 0.f;

		
};
