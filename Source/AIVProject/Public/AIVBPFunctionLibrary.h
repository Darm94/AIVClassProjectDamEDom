// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIVBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AIVPROJECT_API UAIVBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static FVector GetActorLocationInWorld(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static bool GetActorLocationInWorldNew(AActor* InActor, FVector& Location);

	UFUNCTION(BlueprintCallable)
	static bool GetActorWorldLocationAndName(AActor* Actor, FVector& Location, FString& Name);

	UFUNCTION(BlueprintCallable)
	static bool SetActorWorldLocation(AActor* Actor, FVector Location);

	UFUNCTION(BlueprintCallable)
	static FVector GetActorScale3D(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static bool SetActorScale3D(AActor* Actor, FVector Scale);

	UFUNCTION(BlueprintCallable)
	static FRotator GetActorWorldRotation(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static bool SetActorWorldRatation(AActor* Actor, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	static bool CharacterJump(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	static bool CharacterDoubleJump(ACharacter* Character, bool bCanDoubleJump, bool& bOutCanDoubleJump, float LaunchForce = 1000);

	UFUNCTION(BlueprintCallable)
	static bool SetDynamicMaterialOnStaticMesh(UStaticMeshComponent* StaticMeshComponent, int32 MaterialIndex, UMaterialInstanceDynamic*& OutDynamicMaterial);

	UFUNCTION(BlueprintCallable)
	static bool ChangeMaterialVectorParameter(UMaterialInterface* Material, FName ParameterName, FVector4 VectorParam);

	UFUNCTION(BlueprintCallable)
	static bool ChangeMaterialTextureParameter(UMaterialInterface* Material, FName ParameterName, UTexture* TextureParam);
	
};
