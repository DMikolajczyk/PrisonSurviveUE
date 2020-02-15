// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.h"

#include "CellRoom.generated.h"

UCLASS()
class PRISONSURVIVEUE_API ACellRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellRoom();

	UFUNCTION(BlueprintCallable, Category="CellProperties")
	int GetCellID();

	UFUNCTION(BlueprintCallable, Category = "CellProperties")
	void SetCellID(int Number);

	UPROPERTY(VisibleAnywhere, Category = "CellObjects")
	ASlidingDoor* Door;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	/**Prisoner can find own cell by this unique number*/
	UPROPERTY(VisibleAnywhere, Category = "CellProperties")
	int Cell_ID;

	

	void AssignObjectsToParameters();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
