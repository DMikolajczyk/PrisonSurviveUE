// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoByPlayer.h"
#include "PrisonerControllerAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackboardKeys.h"



UBTTask_GoByPlayer::UBTTask_GoByPlayer(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Go by player");
}

EBTNodeResult::Type UBTTask_GoByPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	APrisonerControllerAI* const ControllerAI = Cast<APrisonerControllerAI>(OwnerComponent.GetAIOwner());
	FVector const PlayerLocation = ControllerAI->GetBlackboardComponent()->GetValueAsVector(bbKeys::TargetLocation);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(ControllerAI, PlayerLocation);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}