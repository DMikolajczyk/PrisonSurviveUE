// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"


UCLASS()
class PRISONSURVIVEUE_API ASlidingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float StaticDoorWidth;
	void UpdateParameters();
	
	/**Mesh which presents static part of sliding door*/
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* DoorStatic;

	/**Mesh which presents moving part of sliding door*/
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* DoorDynamic;

	/**Offset distance between two parts of door*/
	UPROPERTY(EditAnywhere, Category = "Transforms")
	float Offset;

	/**Position of moving part when it is closed*/
	UPROPERTY(VisibleAnywhere, Category = "Transforms")
	FVector DoorPositionClosed;

	/**Position of moving part when it is opened*/
	UPROPERTY(VisibleAnywhere, Category = "Transforms")
	FVector DoorPositionOpened;

	

};
