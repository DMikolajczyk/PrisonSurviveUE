// Fill out your copyright notice in the Description page of Project Settings.


#include "PrisonerControllerAI.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PrisonerCharacterAI.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"
#include "PrisonSurviveUECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

APrisonerControllerAI::APrisonerControllerAI(const FObjectInitializer& ObjInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	PrisonerAI = nullptr;
	TargetedCharacter = nullptr;
	
	BehaviorTreeComp = ObjInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackboardComp = ObjInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	

	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	//SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	
	
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &APrisonerControllerAI::OnPawnDetected);
	
}

void APrisonerControllerAI::BeginPlay()
{
	Super::BeginPlay();
	if (SightConfig == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Sight config assign!"));
	}
	else
	{
		/*SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = LoseSightRadius + SightRadius;
		SightConfig->PeripheralVisionAngleDegrees = FieldOfView;
		SightConfig->SetMaxAge(SightAge);
		*/
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}

	//SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	/*
	PrisonerAI = Cast<APrisonerCharacterAI>(GetPawn());

	if (PrisonerAI->NextWaypoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No NextWaypoint assign"));
	}
	*/
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);
	
	UE_LOG(LogTemp, Warning, TEXT("AI begin play"));
}

void APrisonerControllerAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("Posses"));

	if (BlackboardComp != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset); 
	}

}

void APrisonerControllerAI::OnUnPossess()
{
	Super::OnUnPossess();
	UE_LOG(LogTemp, Warning, TEXT("Unposses"));
}

void APrisonerControllerAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*if ((PrisonerAI->NextWaypoint != nullptr) && (TargetedCharacter == nullptr))
	{
		MoveToActor(PrisonerAI->NextWaypoint, 5.0f);
	}
	else if (TargetedCharacter != nullptr)
	{
		MoveToActor(TargetedCharacter);
	}*/
}

FRotator APrisonerControllerAI::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return GetPawn()->GetActorRotation();
}

void APrisonerControllerAI::OnPawnDetected(const TArray<AActor*> &DetectedPawns)
{
	for (AActor* DetectedActor : DetectedPawns)
	{
		APrisonSurviveUECharacter* CharacterPlayer = Cast<APrisonSurviveUECharacter>(DetectedActor);
		if ((CharacterPlayer) && (!GetBlackboardComponent()->GetValueAsBool(bbKeys::CanSeePlayer)))
		{
			UE_LOG(LogTemp, Warning, TEXT("AI %s spotted player"), *GetName());
			GetBlackboardComponent()->SetValueAsBool(bbKeys::CanSeePlayer, true);
		}
		else if ((CharacterPlayer) && (GetBlackboardComponent()->GetValueAsBool(bbKeys::CanSeePlayer)))
		{
			UE_LOG(LogTemp, Warning, TEXT("AI %s lost player"), *GetName());
			GetBlackboardComponent()->SetValueAsBool(bbKeys::CanSeePlayer, false);
		}
	}
	/*for (AActor* DetectedActor : DetectedPawns) 
	{
		if (ActorsInRange.Contains(DetectedActor))
		{
			ActorsInRange.Remove(DetectedActor);
			if (DetectedActor == TargetedCharacter)
			{
				if (ActorsInRange.Num() > 0)
				{
					TargetedCharacter = ActorsInRange[0];
				}
				else
				{
					TargetedCharacter = nullptr;
				}
			}
		}
		else
		{
			ActorsInRange.Add(DetectedActor);
			if (TargetedCharacter == nullptr)
			{
				TargetedCharacter = DetectedActor;
			}
		}
		
	}*/
	//UE_LOG(LogTemp, Warning, TEXT("AI %s spotting %d actors"), *GetName() ,ActorsInRange.Num());
	
}


UBlackboardComponent* APrisonerControllerAI::GetBlackboardComponent() const
{
	return BlackboardComp;
}