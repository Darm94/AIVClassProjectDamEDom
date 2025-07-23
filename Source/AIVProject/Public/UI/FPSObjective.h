// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSObjective.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UFPSObjective : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KeyText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KilledEnemies;
};
