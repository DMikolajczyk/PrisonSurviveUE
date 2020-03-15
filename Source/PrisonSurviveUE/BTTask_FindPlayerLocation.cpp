// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "PrisonerControllerAI.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BlackboardKeys.h"


UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(const FObjectInitializer& objectInitializer)
{
	NodeName = TEXT("Find player location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APrisonerControllerAI* const ControllerAI = Cast<APrisonerControllerAI>(ownerComponent.GetAIOwner());

	FVector const PlayerLocation = Player->GetActorLocation();
	if (IsRandomSearch)
	{
		FNavLocation NavLocation;

		UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, NavLocation, nullptr))
		{
			ControllerAI->GetBlackboardComponent()->SetValueAsVector(bbKeys::TargetLocation, NavLocation.Location);
		}
	}
	else
	{
		ControllerAI->GetBlackboardComponent()->SetValueAsVector(bbKeys::TargetLocation, PlayerLocation);
	}

	FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
