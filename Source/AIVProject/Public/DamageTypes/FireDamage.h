// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "FireDamage.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UFireDamage : public UDamageType
{
	GENERATED_BODY()

public:
	UFireDamage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage Type")
	bool bIgnoresArmor = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage Type")
	float DamageMultiplier = 0.75f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage Type")
	bool bIsDOT = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage Type")
	FName AppliesStatusEffect = FName("Burning");
};
