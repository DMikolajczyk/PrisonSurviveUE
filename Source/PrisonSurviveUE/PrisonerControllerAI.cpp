// Fill out your copyright notice in the Description page of Project Settings.


#include "PrisonerControllerAI.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PrisonerCharacterAI.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"
#include "PrisonSurviveUECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APrisonerControllerAI::APrisonerControllerAI(const FObjectInitializer& ObjInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SightRadius = 500.0f;
	SightAge = 5.0f;
	LoseSightRadius = 200.0f;
	FieldOfView = 80;
	DistanceOffsetToTarget = 50.0f;

	PrisonerAI = nullptr;
	TargetedCharacter = nullptr;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	   
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &APrisonerControllerAI::OnPawnDetected);
	
	BehaviorTreeComp = ObjInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackboardComp = ObjInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

}

void APrisonerControllerAI::BeginPlay()
{
	Super::BeginPlay();

	/*SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LoseSightRadius + SightRadius;
	SightConfig->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfig->SetMaxAge(SightAge);
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
 
	PrisonerAI = Cast<APrisonerCharacterAI>(GetPawn());

	if (PrisonerAI->NextWaypoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No NextWaypoint assign"));
	}
	*/
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);

}

void APrisonerControllerAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("Posses"));

	if (BlackboardComp)
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
		
	}
	//UE_LOG(LogTemp, Warning, TEXT("AI %s spotting %d actors"), *GetName() ,ActorsInRange.Num());
	
}


UBlackboardComponent* APrisonerControllerAI::GetBlackboardComponent() const
{
	return BlackboardComp;
}