// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSReplicatedCharacter.generated.h"

UCLASS()
class AIVPROJECT_API AFPSReplicatedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSReplicatedCharacter();

	//Replicated to every client
	UPROPERTY(ReplicatedUsing=OnRep_HealthChanged)
	int32 Health = 100;

	//Replicated only to owner
	UPROPERTY(Replicated)
	int32 Ammo = 30;

	UFUNCTION()
	void OnRep_HealthChanged();

	//Invoked by Client, executed on server
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPing();

	//Invoked by server executed only on owner client
	UFUNCTION(Client, Unreliable)
	void ClientPing();

	UFUNCTION(NetMulticast, Reliable)
	void AllClientsPing();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerChangeHealth(int32 Delta);

	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const override;

	void TakeDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
