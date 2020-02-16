// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActionHint.h"

ATriggerActionHint::ATriggerActionHint() 
{
	Text = TEXT("Default text");
	OnActorBeginOverlap.AddDynamic(this, &ATriggerActionHint::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ATriggerActionHint::OnEndOverlap);
	//Player = GetWorld()->GetFirstPlayerController()->GetCharacter()

	HintsText = {
		"One",
		"Two",
		"Three"
	};

}

void ATriggerActionHint::BeginPlay()
{
	Super::BeginPlay();
	Text = HintsText[1];
}

void ATriggerActionHint::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (Cast<APrisonSurviveUECharacter>(OtherActor)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision with player detected "));
		APrisonSurviveUECharacter* Tmp = Cast<APrisonSurviveUECharacter>(OtherActor);
		Cast<AUI_Manager>(Tmp->MyUIManager)->ShowHint(Text);
	}
	
}

void ATriggerActionHint::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (Cast<APrisonSurviveUECharacter>(OtherActor)))
	{
		UE_LOG(LogTemp, Warning, TEXT("End of player collision "));
		APrisonSurviveUECharacter* Tmp = Cast<APrisonSurviveUECharacter>(OtherActor);
		Cast<AUI_Manager>(Tmp->MyUIManager)->HideHint();
	}
}