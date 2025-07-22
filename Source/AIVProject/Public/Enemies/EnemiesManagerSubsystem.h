// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BaseEnemy.h"
#include "EnemiesManagerSubsystem.generated.h"

//void FuncName();
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerceived, AActor*, ActorSoundingAlarm, AActor*, ActorTriggeringAlarm);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyTracked, AActor*);

//
//DECLARE_DELEGATE_RetVal(int32, FDelegateRetVal);
//DECLARE_DELEGATE_RetVal_OneParam(int32, FDelegateRetParam, float);
/**
 * 
 */
UCLASS()
class AIVPROJECT_API UEnemiesManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPerceived OnSoundAlarm;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPerceived OnHighAlert;

	FOnEnemyTracked OnEnemyAdded;
	FOnEnemyTracked OnEnemyRemoved;

	UFUNCTION(BlueprintCallable)
	TArray<ABaseEnemy*> SpawnBaseEnemies(int32 NumEnemies, FVector Location);

	UFUNCTION(BlueprintCallable)
	AGenericEnemy* SpawnEnemy(UClass* ClassTospawn, FTransform InTransform);

	inline TArray<AGenericEnemy*> GetActiveEnemies() { return ActiveEnemies; };

	void UnregisterActiveEnemy(AGenericEnemy* EnemyToRemove);
	void RegisterActiveEnemy(AGenericEnemy* EnemyToAdd);

private:
	TArray<AGenericEnemy*> ActiveEnemies;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemiesOnAlarm(AActor* ActorSoundingAlarm, AActor* ActorTriggeringAlarm);

	UFUNCTION(BlueprintCallable)
	void TriggerEnemiesHighAlert(AActor* ActorSoundingAlarm, AActor* ActorTriggeringAlarm);
};




//DECLARE_DELEGATE(FMyDummyDelegate); //only cpp. Can bind a single function, if a second function is bound it replaces the first one
//DECLARE_DYNAMIC_DELEGATE(FMyDynamicDelegate); //accessible through blueprints too. Can bind single function
//DECLARE_MULTICAST_DELEGATE(FMyMulticastDelegate); //cpp only cna bind multiple functions
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyDynamicMulticastDelegate); //Accessible through blueprints too. Can Bind Multiple functions
//
//
//DECLARE_DELEGATE_OneParam(FDelegateWithOneParam, int32);
//DECLARE_DELEGATE_TwoParams(FDelegateWithTwoParam, int32, float);
//DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateDynOneParam, int32, IntParam);
//DECLARE_MULTICAST_DELEGATE_OneParam(FMultiOneParam, int32);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyMultiOneParam, int32, MyIntValue);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMyMultiTwoParam, int32, MyIntValue, float, myfloat);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyMultiParamRef, int32&, MyIntReference);


//FMyDummyDelegate OnSomeAction;
////void MyFunc();
//FMyMulticastDelegate OnMulticastEvent;

//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//FMyDynamicDelegate OnDynamicDelegate;

//UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
//FMyDynamicMulticastDelegate OnMulticastDynamic;

//FDelegateWithOneParam OnDelegateWithOneParam;
////void MyFunc2(int32 myint);

//FDelegateRetVal OnDelegateRetVal;
////int32 MyFunc3();

//FDelegateRetParam OnDelegateRetParam;
////int32 MyFunc4(float MyFloat);

//FMyMultiOneParam OnFMyMultiOneParam;
