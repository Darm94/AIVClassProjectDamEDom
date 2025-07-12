// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSInteractable.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Components/SceneCaptureComponent2D.h"
#include "FPSCharacter.generated.h"

UCLASS()
class AIVPROJECT_API AFPSCharacter : public ACharacter, public IGenericTeamAgentInterface//, public IFPSInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MakeSomeNoise(float Loudness, AActor* NoiseInstigator, FVector Location, USoundBase* Sound);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	class UCameraComponent* FPSCamera;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliSource;

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; };

#pragma region Movement
	//Movement
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
#pragma endregion

#pragma region Actions

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float InteractThreshold = 0.95f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractRadius = 200.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAimAssist = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ShootThreshold = 0.95f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ShootDistance = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootPotency = 1.0f;

	void Interact();
	void Shoot();
	//void ReloadAmmo();
	void LaunchPebble(float Force);

#pragma endregion

#pragma region UI
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 CurrentAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveSlotName = "DefaultSaveSlot";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SaveUserID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InvertYAxis = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadDuration = 2.0f;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 IncomingDamage);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minimap")
	USceneCaptureComponent2D* MinimapCaptureComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextureRenderTarget2D* MinimapRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* MinimapIconTexture;

private:
	void SaveGame();

	void LoadGame();

	FGenericTeamId TeamID;

	class UFPSHUDWidget* HUDWidget;
	FTimerHandle ReloadTimerHandle;

	TArray<AActor*> MinimapTrackedActors;

};
