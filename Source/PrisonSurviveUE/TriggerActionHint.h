// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PrisonSurviveUECharacter.h"
#include "UI_Manager.h"
#include "TriggerActionHint.generated.h"


/**
 * 
 */
UCLASS()
class PRISONSURVIVEUE_API ATriggerActionHint : public ATriggerBox
{
	GENERATED_BODY()
/*
protected:
	virtual void BeginPlay() override;
	

public:
	ATriggerActionHint();

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);


	*/

protected:
	virtual void BeginPlay() override;
public:
	ATriggerActionHint();

	UPROPERTY(EditAnywhere)
	FString Text;

	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	TArray <FString> HintsText;

};