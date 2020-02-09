// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellRoom.generated.h"

UCLASS()
class PRISONSURVIVEUE_API ACellRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellRoom();

	UFUNCTION(BlueprintCallable, Category="m cell properties")
	int GetCellID();

	UFUNCTION(BlueprintCallable, Category = "m cell properties")
	void SetCellID(int Number);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**Prisoner can find own cell by this unique number*/
	UPROPERTY(VisibleAnywhere, Category = "m cell properties")
	int Cell_ID;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
