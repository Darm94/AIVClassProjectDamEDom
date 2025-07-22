// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Items/MyFloatingItem.h"

// Sets default values
AMyFloatingItem::AMyFloatingItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFloatingItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFloatingItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

