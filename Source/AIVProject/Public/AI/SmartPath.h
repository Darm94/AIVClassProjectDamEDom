// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartPath.generated.h"

UCLASS()
class AIVPROJECT_API ASmartPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmartPath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* SplineComponent;

	UFUNCTION()
	TArray<FVector> GetSplinePoints();

	UFUNCTION()
	FVector GetSplinePointAtIndex(int32 Index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
