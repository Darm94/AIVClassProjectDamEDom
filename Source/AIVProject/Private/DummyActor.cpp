// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADummyActor::ADummyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ADummyActor::BeginPlay()
{
	Super::BeginPlay();

	//TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), DummyActorsArray);

	//DummyActorsArray.Add();
	
}

// Called every frame
void ADummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADummyActor::PrintMessage(FString Message)
{
	UE_LOG(LogTemp, Warning, TEXT("My message: %s"), *Message);
	
}

void ADummyActor::PrintLocation()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Location.ToString());
}

void ADummyActor::TeleportToLocation(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}

