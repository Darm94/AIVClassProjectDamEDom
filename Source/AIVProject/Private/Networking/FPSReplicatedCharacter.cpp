// Fill out your copyright notice in the Description page of Project Settings.


#include "Networking/FPSReplicatedCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSReplicatedCharacter::AFPSReplicatedCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; // Replicates the whole actor
	SetReplicateMovement(true); // replicates movements and rotations
}

void AFPSReplicatedCharacter::OnRep_HealthChanged()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Health has been modified for %s: %d"),*GetName(),Health));
	}
}

void AFPSReplicatedCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Health always replicated to all clients
	DOREPLIFETIME(AFPSReplicatedCharacter, Health);


	//Ammo always replicated on condition: only to owner
	DOREPLIFETIME_CONDITION(AFPSReplicatedCharacter, Ammo, COND_OwnerOnly);
}

void AFPSReplicatedCharacter::TakeDamage()
{
	ServerChangeHealth(2);
}

// Called when the game starts or when spawned
void AFPSReplicatedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSReplicatedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("MyCharacter: %s MyHealth: %d"), *GetName(), Health));
	}

}

// Called to bind functionality to input
void AFPSReplicatedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Ping", IE_Pressed, this, &AFPSReplicatedCharacter::ServerPing);
	InputComponent->BindAction("TakeDamage", IE_Pressed, this, &AFPSReplicatedCharacter::TakeDamage);
}

bool AFPSReplicatedCharacter::ServerPing_Validate()
{
	//do all your anticheats code
	return true;
}

void AFPSReplicatedCharacter::ServerPing_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Server: Ping ricevuto"));
	ClientPing();
	AllClientsPing();
}

void AFPSReplicatedCharacter::ClientPing_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Client ping received"));
	}
}

void AFPSReplicatedCharacter::AllClientsPing_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" All Clients ping received"));
	}
}

bool AFPSReplicatedCharacter::ServerChangeHealth_Validate(int32 Delta)
{
	if (Delta > 5)
	{
		return false;
	}
	return true;
}

void AFPSReplicatedCharacter::ServerChangeHealth_Implementation(int32 Delta)
{

	Health = Health + Delta;
	//if (HasAuthority())
	//{
	//	OnRep_HealthChanged();
	//}

	if (GetNetMode() == NM_ListenServer)
	{
		OnRep_HealthChanged();
	}
}