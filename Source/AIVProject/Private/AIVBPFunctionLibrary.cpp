// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVBPFunctionLibrary.h"
#include "GameFramework/Character.h"


FVector UAIVBPFunctionLibrary::GetActorLocationInWorld(AActor* Actor)
{
	if (Actor)
	{
		return Actor->GetActorLocation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Blueprint function GetActorLocationInWorld has been given an invalid actor as argument."));
		return FVector::Zero();
	}
}

bool UAIVBPFunctionLibrary::GetActorLocationInWorldNew(AActor* InActor, FVector& Location)
{
	if (!InActor || !InActor->GetRootComponent())
	{
		return false;
	}

	Location = InActor->GetActorLocation();
	return true;
}

bool UAIVBPFunctionLibrary::GetActorWorldLocationAndName(AActor* Actor, FVector& Location, FString& Name)
{
	if (!Actor || !Actor->GetRootComponent())
	{
		return false;
	}

	Location = Actor->GetActorLocation();
	Name = Actor->GetName();
	return true;
}

bool UAIVBPFunctionLibrary::SetActorWorldLocation(AActor* Actor, FVector Location)
{
	return Actor->SetActorLocation(Location);
}


FVector UAIVBPFunctionLibrary::GetActorScale3D(AActor* Actor)
{
	return Actor->GetActorScale();
}

bool UAIVBPFunctionLibrary::SetActorScale3D(AActor* Actor, FVector Scale)
{
	if (!Actor || !Actor->GetRootComponent())
	{
		return false;
	}
	Actor->SetActorScale3D(Scale);
	return true;
}


FRotator UAIVBPFunctionLibrary::GetActorWorldRotation(AActor* Actor)
{
	return Actor->GetActorRotation();
}

bool UAIVBPFunctionLibrary::SetActorWorldRatation(AActor* Actor, FRotator Rotation)
{
	return Actor->SetActorRotation(Rotation);
}

bool UAIVBPFunctionLibrary::CharacterJump(ACharacter* Character)
{
	if (!Character || !Character->GetRootComponent())
	{
		return false;
	}

	Character->Jump();
	return true;
}

bool UAIVBPFunctionLibrary::CharacterDoubleJump(ACharacter* Character, bool bCanDoubleJump, bool& bOutCanDoubleJump, float LaunchForce)
{
	if (!Character || !Character->GetRootComponent())
	{
		return false;
	}

	if (!Character->CanJump() && bCanDoubleJump)
	{
		FVector JumpDirection = Character->GetActorUpVector();
		FVector JumpIntensity = JumpDirection * LaunchForce;
		Character->LaunchCharacter(JumpIntensity, false, false);
		bOutCanDoubleJump = false;
	}
	else if(Character->CanJump())
	{
		Character->Jump();
		bOutCanDoubleJump = true;
	}

	return true;
}

bool UAIVBPFunctionLibrary::SetDynamicMaterialOnStaticMesh(UStaticMeshComponent* StaticMeshComponent, int32 MaterialIndex, UMaterialInstanceDynamic*& OutDynamicMaterial)
{
	if (StaticMeshComponent)
	{
		UMaterialInterface* StaticMeshMaterial = StaticMeshComponent->GetMaterial(MaterialIndex);
		if (!StaticMeshMaterial)
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid index:%d for material on %s"), MaterialIndex, *StaticMeshComponent->GetName());
			return false;
		}
		OutDynamicMaterial = Cast<UMaterialInstanceDynamic>(StaticMeshMaterial);
		if (!OutDynamicMaterial)
		{
			OutDynamicMaterial = UMaterialInstanceDynamic::Create(StaticMeshMaterial, StaticMeshComponent);
			StaticMeshComponent->SetMaterial(MaterialIndex, OutDynamicMaterial);
			return true;
		}
		else
		{
			return true;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("Invalid static mesh component."));
	return false;
}

bool UAIVBPFunctionLibrary::ChangeMaterialVectorParameter(UMaterialInterface* Material, FName ParameterName, FVector4 VectorParam)
{
	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
	if (!DynamicMaterial)
	{
		return false;
	}
	else
	{
		DynamicMaterial->SetVectorParameterValue(ParameterName, VectorParam);
		return true;
	}
}

bool UAIVBPFunctionLibrary::ChangeMaterialTextureParameter(UMaterialInterface* Material, FName ParameterName, UTexture* TextureParam)
{
	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
	if (!DynamicMaterial)
	{
		return false;
	}
	else
	{
		DynamicMaterial->SetTextureParameterValue(ParameterName, TextureParam);
		return true;
	}
}
