// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DummyActor.generated.h"

UCLASS()
class AIVPROJECT_API ADummyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DummyCategory")
	int32 DummyInt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DummyCategory")
	int64 DummyInt64;

	UPROPERTY()
	uint32 DummyUint;

	float DummyFloat;
	double DummyDouble;
	bool DummyBool;

	FString DummyString;
	FName DummyName;
	FText DummyText;

	FVector DummyVector;
	FVector2D Dummy2DVector;
	
	FQuat DummyQuaternion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> DummyActorsArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FTransform DummyTransform;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FRotator DummyRotator;
	
	TMap<int32, AActor*> DummyIndexActorDictionary;

	UFUNCTION(BlueprintCallable)
	void PrintMessage(FString Message);

	UFUNCTION(BlueprintCallable)
	void PrintLocation();

	UFUNCTION(BlueprintCallable)
	void TeleportToLocation(FVector NewLocation);


};
