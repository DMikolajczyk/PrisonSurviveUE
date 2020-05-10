// Fill out your copyright notice in the Description page of Project Settings.


#include "PrisonerAIController.h"


APrisonerAIController::APrisonerAIController()
{

}

void APrisonerAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Controller AI"));
}


