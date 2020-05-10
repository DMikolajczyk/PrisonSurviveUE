// Fill out your copyright notice in the Description page of Project Settings.


#include "PrisonerCharacterAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Waypoint.h"

// Sets default values
APrisonerCharacterAI::APrisonerCharacterAI()
{
	// Delete licking walls by characters - charackter will be rotated to direction which he walking, not for target.
	bUseControllerRotationYaw = false;

	// Rotate Character to moving direction
	GetCharacterMovement()->bOrientRotationToMovement = true;

	RotationSpeed = 600;	
}

// Called when the game starts or when spawned
void APrisonerCharacterAI::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->RotationRate.Yaw = RotationSpeed;	
}


// Called to bind functionality to input
/*void APrisonerCharacterAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

