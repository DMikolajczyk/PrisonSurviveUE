// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PrisonerCharacterAI.generated.h"

UCLASS()
class PRISONSURVIVEUE_API APrisonerCharacterAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APrisonerCharacterAI();

	/** How fast character rotate when he change direction of moving*/
	UPROPERTY(EditAnywhere, Category = "Moving parameters")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI options")
	class AWaypoint* NextWaypoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
