// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "PrisonerCharacterAI.h"
#include "BTTask_GoByPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PRISONSURVIVEUE_API UBTTask_GoByPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_GoByPlayer(const FObjectInitializer& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

};
