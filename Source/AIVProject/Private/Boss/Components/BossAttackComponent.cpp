// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/Components/BossAttackComponent.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DamageTypes/FireDamage.h"

// Sets default values for this component's properties
UBossAttackComponent::UBossAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	// ...
	
}


// Called every frame
void UBossAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBossAttackComponent::PerformMelee()
{
	if (AActor* Owner = GetOwner())
	{
		//Sphere trace or overlap to apply melee damage
		TArray<FHitResult> HitResults;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		bool bSuccess = GetWorld()->SweepMultiByChannel(HitResults, GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100.0f, GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100.0f, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(100.0f), CollisionParams);
		if (bSuccess)
		{
			for (FHitResult HitResult : HitResults)
			{
				AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(HitResult.GetActor());
				if (FPSCharacter)
				{
					APawn* OwnerPawn = Cast<APawn>(GetOwner());

					UGameplayStatics::ApplyDamage(FPSCharacter, MeleeDamage, OwnerPawn->GetController(), GetOwner(), UDamageType::StaticClass());
					//UGameplayStatics::ApplyDamage(FPSCharacter, MeleeDamage, OwnerPawn->GetController(), GetOwner(), UFireDamage::StaticClass());
					//ApplyDamage will trigger the OnTakeAnyDamage event on the actor that has been damaged
					//For it to have any effect you will need to create a function in your FPSCharacter with the specific signature:
					//UFUNCTION()
					//void FunctionName(AActor * DamagedActor, float Damage, const UDamageType * DmgType, AController * InstigatedBy, AActor * Causer);
					//And then remember to bind that function to the OnTakeAnyDamage event.
					//Inside that function you can manage health reduction and any reaction to the damage
				}
			}
		}
	}
}

void UBossAttackComponent::PerformRanged()
{
	if (ProjectileClass && GetOwner())
	{
		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200.0f;
		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
		CurrentAmmo--;
	}
}

void UBossAttackComponent::PerformCharge()
{
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		OwnerCharacter->LaunchCharacter(OwnerCharacter->GetActorForwardVector() * 1000.0f * ChargeSpeedMultiplier, true, true);
	}
}

