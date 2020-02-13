// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickable.generated.h"

UCLASS()
class PRISONSURVIVEUE_API AItemPickable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**Action which player can do after click Action button*/
	void Action();


	/**Mesh which represents item in the game world*/
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "ItemParameters")
	FString Name;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
