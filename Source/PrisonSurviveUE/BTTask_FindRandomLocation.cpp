// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "PrisonerControllerAI.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackboardKeys.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(const FObjectInitializer& objectInitializer)
{
	NodeName = TEXT("Find random location");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	APrisonerControllerAI* const Controller = Cast<APrisonerControllerAI>(ownerComponent.GetAIOwner());
	APawn* const Pawn = Controller->GetPawn();

	FVector const Origin = Pawn->GetActorLocation();
	FNavLocation Location;

	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location, nullptr))
	{
		Controller->GetBlackboardComponent()->SetValueAsVector(bbKeys::TargetLocation, Location.Location);
	}

	FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
