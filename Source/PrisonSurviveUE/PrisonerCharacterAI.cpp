// Fill out your copyright notice in the Description page of Project Settings.


#include "PrisonerCharacterAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Waypoint.h"

// Sets default values
APrisonerCharacterAI::APrisonerCharacterAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void APrisonerCharacterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
/*void APrisonerCharacterAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

