// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SmartPath.h"
#include "Components/SplineComponent.h"

// Sets default values
ASmartPath::ASmartPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

TArray<FVector> ASmartPath::GetSplinePoints()
{
	TArray<FVector> OutPoints;
	int32 NumOfPoints = SplineComponent->GetNumberOfSplinePoints();
	for (int32 SplinePointIndex = 0; SplinePointIndex < NumOfPoints; SplinePointIndex++)
	{
		OutPoints.Add(SplineComponent->GetLocationAtSplinePoint(SplinePointIndex, ESplineCoordinateSpace::World));
	}
	return OutPoints;
}

FVector ASmartPath::GetSplinePointAtIndex(int32 Index)
{
	return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
}

// Called when the game starts or when spawned
void ASmartPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmartPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

