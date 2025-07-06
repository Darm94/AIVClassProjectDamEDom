// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AIVPROJECT_API IFPSInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool TriggerInteraction(AActor* Instigator);
	virtual bool TriggerHit(AActor* Instigator);

	//Callable and overridable in blueprint. If defined in cpp needs to be defined as MyFunction_Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TriggerBlueprintHit(AActor* Instigator);

	//Callable and overridable in blueprint. If defined in cpp needs to be defined as MyFunction_Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TriggerBlueprintInteract(AActor* Instigator);

	//Doesn't need a cpp deifnition, can be implemented in blueprints
	UFUNCTION(BlueprintImplementableEvent)
	void MYBPFunction(AActor* Instigator);
};
