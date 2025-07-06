// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& SlotName, int32 UserIndex);

	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName, int32 UserIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	FString CheckPointSlotName = "Checkpoint";

	//Add slotname and userindex for load in the option of having more levels.

	
};
