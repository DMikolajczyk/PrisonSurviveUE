// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PrisonSurviveUECharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// APrisonSurviveUECharacter

APrisonSurviveUECharacter::APrisonSurviveUECharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	HealthMax = 100;
	Health = HealthMax;
	WalkSpeed = 300;
	RunSpeed = 600;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	/*Door = NULL;
	InfoWidget = nullptr;*/
}


void APrisonSurviveUECharacter::BeginPlay()
{
	Super::BeginPlay();
	if (InfoWidget)
	{
		InfoWidgetObj = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), InfoWidget);
		if (InfoWidgetObj)
		{
			InfoWidgetObj->AddToViewport();
			SetVisibilityOfInfo(ESlateVisibility::Hidden, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APrisonSurviveUECharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); 
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APrisonSurviveUECharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APrisonSurviveUECharacter::SprintStop);

	PlayerInputComponent->BindAction("HealTest", IE_Pressed, this, &APrisonSurviveUECharacter::HealTest);
	PlayerInputComponent->BindAction("DamageTest", IE_Pressed, this, &APrisonSurviveUECharacter::DamageTest);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APrisonSurviveUECharacter::OnAction);

	PlayerInputComponent->BindAxis("MoveForward", this, &APrisonSurviveUECharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APrisonSurviveUECharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APrisonSurviveUECharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APrisonSurviveUECharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &APrisonSurviveUECharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APrisonSurviveUECharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APrisonSurviveUECharacter::OnResetVR);
}


void APrisonSurviveUECharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void APrisonSurviveUECharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void APrisonSurviveUECharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void APrisonSurviveUECharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APrisonSurviveUECharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APrisonSurviveUECharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APrisonSurviveUECharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APrisonSurviveUECharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APrisonSurviveUECharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APrisonSurviveUECharacter::Heal(int Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Character healed by value: %d"), Amount);
	Health += Amount;
	if (Health > HealthMax)
	{
		Health = HealthMax;
	}
}

void APrisonSurviveUECharacter::HealTest()
{
	Heal(10);
}

void APrisonSurviveUECharacter::TakeDamage(int Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage has been taken with value: %d"), Amount);
	Health -= Amount;
	if (Health < 0)
	{
		Health = 0;
	}
}

void APrisonSurviveUECharacter::DamageTest()
{
	TakeDamage(10);
	
	
}

#if WITH_EDITOR 
void APrisonSurviveUECharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(APrisonSurviveUECharacter, HealthMax)))
	{
		Health = HealthMax;
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

/*void APrisonSurviveUECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InfoWidget)
	{
		InfoWidget->GetWidgetFromName("doorOpeningInfo")->SetVisibility(ESlateVisibility::Visible);
	}
	
	//Door = Cast<ASlidingDoor>

}
*/
void APrisonSurviveUECharacter::OnAction()
{
	/*if (Door)
	{
		Door->ToggleDoor();
	}*/
}

void APrisonSurviveUECharacter::SetVisibilityOfInfo(ESlateVisibility Visibility, int Option)
{
	switch (Option)
	{
		case 0:
			InfoWidgetObj->GetWidgetFromName("doorOpenInfo")->SetVisibility(Visibility);
			InfoWidgetObj->GetWidgetFromName("doorCloseInfo")->SetVisibility(Visibility);
			break;
		case 1:
			InfoWidgetObj->GetWidgetFromName("doorOpenInfo")->SetVisibility(Visibility);
			break;
		case 2:
			InfoWidgetObj->GetWidgetFromName("doorCloseInfo")->SetVisibility(Visibility);
			break;

	}
}

void APrisonSurviveUECharacter::SampleFun()
{
}
