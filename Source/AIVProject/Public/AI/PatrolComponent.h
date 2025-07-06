// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/StateComponent.h"
#include "SmartPath.h"
#include "PatrolComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class AIVPROJECT_API UPatrolComponent : public UStateComponent
{
	GENERATED_BODY()

public:
	UPatrolComponent();

	virtual void EnterState() override;
	virtual void PlayState() override;
	virtual void ExitState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASmartPath* SmartPath;

	//Array of points to patrol. If empty it will be filled considering the other setting variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class ATargetPoint*> TargetPoints; //forward declaration of ATargetPoint

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGeneratePointsAtRuntime = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition="bGeneratePointsAtRuntime"))
	int32 MaxTargetPointsToFind = 10; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bGeneratePointsAtRuntime"))
	float SearchRangeForTargetPoints = 1000.0;

private:
	TArray<AActor*> GenerateTargetPoints(int32 NumPoints,float MaxDistance);

	AActor* CurrentTarget;
	int32 CurrentIndex = 0;
	float TargetDistanceThreshold = 100.0f;
	
};
