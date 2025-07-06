// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIVPROJECT_API UBossAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	float MeleeDamage = 25.0f;

	UPROPERTY(EditAnywhere, Category="Attack")
	float ChargeSpeedMultiplier = 2.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	int32 MaxAmmo = 10;

	UFUNCTION(BlueprintCallable, Category="Attack")
	void PerformMelee();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void PerformRanged();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void PerformCharge();

	inline void SetChargeSpeedMultiplier(float NewMultiplier) { ChargeSpeedMultiplier = NewMultiplier; };
};
