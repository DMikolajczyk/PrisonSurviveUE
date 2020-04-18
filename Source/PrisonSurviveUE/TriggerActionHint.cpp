// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActionHint.h"

ATriggerActionHint::ATriggerActionHint() 
{
	//Text = TEXT("Default text");
	OnActorBeginOverlap.AddDynamic(this, &ATriggerActionHint::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ATriggerActionHint::OnEndOverlap);

	HintsText = {
		"One",
		"Two"
	};

}

void ATriggerActionHint::BeginPlay()
{
	Super::BeginPlay();
}

void ATriggerActionHint::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APrisonSurviveUECharacter* Player = Cast<APrisonSurviveUECharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision with player detected "));
		Player->ShowHint("Test 1254");
	}
}

void ATriggerActionHint::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APrisonSurviveUECharacter* Player = Cast<APrisonSurviveUECharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player left the collision"));
		Player->HideHint();
	}
}