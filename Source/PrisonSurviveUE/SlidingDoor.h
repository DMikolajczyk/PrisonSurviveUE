// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"

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

	UFUNCTION(BlueprintCallable)
	void Close();
	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION()
	void ControlDoor();

	UFUNCTION()
	void ToggleDoor();

	UPROPERTY(EditAnywhere, Category="Animation")
	UCurveFloat* DoorCurve;

	FTimeline Timeline;

	UFUNCTION(BlueprintCallable)
	bool GetIsOpen();
	
	UFUNCTION(BlueprintCallable)
	void SetIsOpen(bool open);

private:
	
	bool bIsOpen;

	/**Value (in seconds) which represents state of playing animation*/
	float PlaybackPosition;
	
	/**Position of moving door with curve correction*/
	float CurveFloatValue;

	void UpdateParameters();



	UPROPERTY(EditAnywhere, Category = "Hierarchy")
	USceneComponent* RootScene;

	/**Mesh which presents static part of sliding door*/
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* DoorStatic;

	/**Mesh which presents moving part of sliding door*/
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* DoorDynamic;

	/**Offset distance between two parts of door*/
	UPROPERTY(EditAnywhere, Category = "Transforms")
	float Offset;
	
	/**Width of static part of door*/
	UPROPERTY(EditAnywhere, Category = "Transforms")
	float StaticDoorWidth;
	
	/**Position of moving part when it is opened*/
	UPROPERTY(VisibleAnywhere, Category = "Transforms")
	FVector DoorPositionOpened;
	

};
