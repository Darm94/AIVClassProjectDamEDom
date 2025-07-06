// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSInteractable.h"

// Add default functionality here for any IFPSInteractable functions that are not pure virtual.

bool IFPSInteractable::TriggerInteraction(AActor* Instigator)
{
	return false;
}

bool IFPSInteractable::TriggerHit(AActor* Instigator)
{
	return false;
}
