// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GenericEnemy.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemies/EnemiesManagerSubsystem.h"
#include "AIController.h"

// Sets default values
AGenericEnemy::AGenericEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////////////////////////////////////////////////////////////
	// //////////////////AI/////////////////////////////////////
	// /////////////////////////////////////////////////////////
	//Create AI perception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	//Create and configure senses
	//Create Sight
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIPerceptionSight"));

	//Configure sight
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	FAISenseAffiliationFilter AffiliationFilter;
	AffiliationFilter.bDetectEnemies = true;
	AffiliationFilter.bDetectFriendlies = false;
	AffiliationFilter.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation = AffiliationFilter;
	SightConfig->SetMaxAge(5.0f);

	//create hearing
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AIPerceptionHearing"));

	//configure hearing
	HearingConfig->HearingRange = 600.0;
	HearingConfig->LoSHearingRange = 1200.0;
	HearingConfig->bUseLoSHearing = true;
	HearingConfig->SetMaxAge(5.0);
	HearingConfig->DetectionByAffiliation = AffiliationFilter;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABaseEnemy::OnPerceptionUpdated);
	/////////////////////////////////////////////////////////////
	/////////////////////END AI//////////////////////////////////
	/////////////////////////////////////////////////////////////

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	//RootComponent->Set CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(42.0f, 96.f);
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);

}

// Called when the game starts or when spawned
void AGenericEnemy::BeginPlay()
{
	Super::BeginPlay();
	UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
	EnemiesManager->RegisterActiveEnemy(this);
	OnDestroyed.AddDynamic(this, &ABaseEnemy::OnActorDelete);

	if (AAIController* AICont = Cast<AAIController>(GetController()))
	{
		//Assuming 'MyPawnPerceptionComponent' is a UAIPerceptionComponent created on the Pawn
		AICont->SetPerceptionComponent(*AIPerceptionComponent);
		//AICont->SetGenericTeamId(FGenericTeamId(1));
	}
	
}

// Called every frame
void AGenericEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenericEnemy::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComponent->GetActorsPerception(Actor, Info);
		if (Info.LastSensedStimuli.Num() > 0)
		{
			for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
			{
				if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>() && Stimulus.WasSuccessfullySensed())
				{
					UE_LOG(LogTemp, Warning, TEXT("Saw actor %s at Location: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
					ReactToSeenActor(Actor, Stimulus.StimulusLocation);
				}
				else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>() && Stimulus.WasSuccessfullySensed())
				{
					UE_LOG(LogTemp, Warning, TEXT("Heard actor %s at Location: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
					ReactToHeardActor(Actor, Stimulus.StimulusLocation);
				}
			}
		}
	}
}

void AGenericEnemy::OnActorDelete(AActor* ActorDestroyed)
{
	UEnemiesManagerSubsystem* EnemiesManager = GetWorld()->GetSubsystem<UEnemiesManagerSubsystem>();
	EnemiesManager->UnregisterActiveEnemy(this);
}

// Called to bind functionality to input
void AGenericEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

