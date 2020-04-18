// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PrisonSurviveUEGameMode.generated.h"

UCLASS(minimalapi)
class APrisonSurviveUEGameMode : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
		
public:
	APrisonSurviveUEGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUD;
	
	UPROPERTY()
	class UUserWidget* PlayerHUDWidget;

};



