// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossPhaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIVPROJECT_API UBossPhaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossPhaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phase")
	float MaxHealth = 1000.0f;

	UPROPERTY(BlueprintReadOnly, Category="Phase")
	float CurrentHealth;

	UPROPERTY(BlueprintAssignable, Category="Phase")
	FOnPhaseEvent OnPhaseTwo;

	UPROPERTY(BlueprintAssignable, Category = "Phase")
	FOnPhaseEvent OnPhaseThree;

	UPROPERTY(BlueprintReadOnly, Category = "Phase")
	int32 CurrentPhase = 1;

	UPROPERTY(EditAnywhere, Category="Phase")
	float PhaseTwoThreshold = 0.5f; //50%

	UPROPERTY(EditAnywhere, Category = "Phase")
	float PhaseThreeThreshold = 0.2f; //20%

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DmgType, AController* InstigatedBy, AActor* Causer);

	void ApplyStatusEffect(FName Status, float DPSDamage);

		
};
