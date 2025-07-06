// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/FireDamage.h"

UFireDamage::UFireDamage()
{
	bIgnoresArmor = true;
	DamageMultiplier = 0.75f;
	bIsDOT = true;
	AppliesStatusEffect = FName("Burning");
}
