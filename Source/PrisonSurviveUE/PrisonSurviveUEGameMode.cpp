// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PrisonSurviveUEGameMode.h"
#include "PrisonSurviveUECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



APrisonSurviveUEGameMode::APrisonSurviveUEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
}


void APrisonSurviveUEGameMode::BeginPlay()
{
	Super::BeginPlay();
	APrisonSurviveUECharacter* MyCharacter = Cast<APrisonSurviveUECharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUD)
	{
		PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUD);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
	if (HintUI)
	{
		InfoWidget = CreateWidget<UUserWidget>(GetWorld(), HintUI);
		if (InfoWidget)
		{
			InfoWidget->AddToViewport();
		}
	}
}