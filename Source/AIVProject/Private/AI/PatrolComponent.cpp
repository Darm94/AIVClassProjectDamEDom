// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrolComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "AIController.h"

UPatrolComponent::UPatrolComponent()
{
	StateType = EState::Patrol;
}

void UPatrolComponent::EnterState()
{
	if (bGeneratePointsAtRuntime)
	{
		GenerateTargetPoints(MaxTargetPointsToFind, SearchRangeForTargetPoints);
	}

	if (!bGeneratePointsAtRuntime && TargetPoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is trying to patrol but target list is empty and not generated at runtime."), *GetOwner()->GetName());
		return;
	}

	if (TargetPoints.Num() > 0)
	{
		CurrentTarget = TargetPoints[CurrentIndex];
		APawn* PawnOwner = Cast<APawn>(GetOwner());
		if (PawnOwner)
		{
			AAIController* AIController = Cast<AAIController>(PawnOwner->GetController());		
			AIController->MoveToActor(CurrentTarget);
			//AIController->MoveToActor()
			//AIController->MoveToLocation()
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No target points found for %s. Impossible to patrol."), *GetOwner()->GetName());
	}
}

void UPatrolComponent::PlayState()
{
	if (TargetPoints.Num() > 0)
	{
		APawn* PawnOwner = Cast<APawn>(GetOwner());
		if (PawnOwner)
		{
			AAIController* AIController = Cast<AAIController>(PawnOwner->GetController());

			if (FVector::Distance(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation()) <= TargetDistanceThreshold)
			{
				CurrentTarget = TargetPoints[++CurrentIndex];
				AIController->MoveToActor(CurrentTarget);
			}
		}
	}
}

void UPatrolComponent::ExitState()
{
}

TArray<AActor*> UPatrolComponent::GenerateTargetPoints(int32 NumPoints, float MaxDistance)
{
	//within MaxDistanceRange
	//Get a Maximum of NumPoints ATargetActor
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Points);
	
	//Get only target points within range
	TArray<AActor*> TargetPointsInRange;
	for (AActor* Point : Points)
	{
		if (FVector::Distance(GetOwner()->GetActorLocation(), Point->GetActorLocation()) <= MaxDistance)
		{
			TargetPointsInRange.Add(Point);
			if (TargetPointsInRange.Num() > NumPoints)
			{
				break;
			}
		}
	}
	return TargetPointsInRange;
}
