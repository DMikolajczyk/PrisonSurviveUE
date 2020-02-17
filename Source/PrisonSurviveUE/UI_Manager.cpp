// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Manager.h"

// Sets default values
AUI_Manager::AUI_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HintText = TEXT("Default text1");
}

// Called when the game starts or when spawned
void AUI_Manager::BeginPlay()
{
	Super::BeginPlay();
	
	

	PlayerStaticWidget = AddWidget(PlayerStaticWidget, PlayerStaticHUD, ESlateVisibility::Visible);
	InfoWidget = AddWidget(InfoWidget, InfoHUD, ESlateVisibility::Hidden);
}

// Called every frame
void AUI_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UUserWidget* AUI_Manager::AddWidget(UUserWidget* Widget, TSubclassOf<class UUserWidget> WidgetHUD, ESlateVisibility Visibility)
{
	if (WidgetHUD)
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetHUD);
		if (Widget)
		{
			Widget->AddToViewport();
			SetVisibilityOfWidget(Widget, Visibility);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NULL in AddWidget function"));
	}
	return Widget;
}

void AUI_Manager::SetVisibilityOfWidget(UUserWidget* Widget, ESlateVisibility Visibility)
{
	Widget->SetVisibility(Visibility);
}

void AUI_Manager::SetVisibilityOfElement(UUserWidget* Widget, FName Name, ESlateVisibility Visibility)
{
	if (Widget) 
	{
		if (Widget->GetWidgetFromName(Name))
		{
			Widget->GetWidgetFromName(Name)->SetVisibility(Visibility);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Widget doesn't have element with name %s"), *Name.ToString());
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NULL in SetVisibilityOfElement function"));
	}
}

void AUI_Manager::ShowHint(FString Text)
{
	SetVisibilityOfWidget(InfoWidget, ESlateVisibility::Visible);
	HintText = Text;
}

void AUI_Manager::HideHint()
{
	SetVisibilityOfWidget(InfoWidget, ESlateVisibility::Hidden);
}
