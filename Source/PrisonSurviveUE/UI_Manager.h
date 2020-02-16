// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "UI_Manager.generated.h"

UCLASS()
class PRISONSURVIVEUE_API AUI_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUI_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerStaticHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> InfoHUD;

	UPROPERTY()
	UUserWidget* PlayerStaticWidget;

	UPROPERTY()
	UUserWidget* InfoWidget;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetVisibilityOfWidget(UUserWidget* Widget, ESlateVisibility Visibility);
	UFUNCTION()
	void SetVisibilityOfElement(UUserWidget* Widget, FName Name, ESlateVisibility Visibility);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString HintText;
	
	UFUNCTION(BlueprintCallable)
	void ShowHint(FString Text);

	UFUNCTION(BlueprintCallable)
	void HideHint();

private:
	UFUNCTION()
	UUserWidget* AddWidget(UUserWidget* Widget, TSubclassOf<class UUserWidget> WidgetHUD, ESlateVisibility Visibility);

	
};
