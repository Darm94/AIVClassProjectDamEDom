// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UFPSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(int32 CurrentHealth);

	UFUNCTION(BlueprintCallable)
	void UpdateAmmo(int32 CurrentAmmo, int32 MaxAmmo);

	UFUNCTION(BlueprintCallable)
	void ShowReloadBar(float Duration);

	UFUNCTION(BlueprintCallable)
	void PlayDamageFlash(float Duration);	
	
	UFUNCTION(BlueprintCallable, Category = "Minimap")
	void UpdateMinimapIcons(const TArray<AActor*>& TrackedActors, UTexture2D* PlayerIconTexture, UTexture2D* EnemyIconTexture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	class AFPSCharacter* MinimapActor;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ReloadBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* CrosshairImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* DamageFlashImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* MinimapImage;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MinimapCanvas;

private:

	FTimerHandle ReloadTimerHandle;
	float ReloadDuration;
	float ReloadElapsedTime;


	void UpdateReloadBar();


	
};
