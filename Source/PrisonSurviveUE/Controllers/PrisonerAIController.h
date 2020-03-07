// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PrisonerAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRISONSURVIVEUE_API APrisonerAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

};
