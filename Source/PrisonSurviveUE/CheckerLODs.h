// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CheckerLODs.generated.h"

UCLASS()
class PRISONSURVIVEUE_API ACheckerLODs : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckerLODs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void PrintStaticMeshesWithoutLOD(int32 MinNumVertices);

	UPROPERTY(EditAnywhere)
	TSet<FString> StaticMeshLODSearchIgnore;
};
