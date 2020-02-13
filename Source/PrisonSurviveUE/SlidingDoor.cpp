// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	DoorStatic = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door static"));
	DoorStatic->AttachToComponent(RootScene, FAttachmentTransformRules::KeepRelativeTransform);
	DoorDynamic = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door dynamic"));
	DoorDynamic->AttachToComponent(RootScene, FAttachmentTransformRules::KeepRelativeTransform);

	Offset = 9.f;
	StaticDoorWidth = 100.f;
	DoorPositionOpened = FVector(0.f, Offset, 0.f);
	DoorPositionClosed = FVector(-StaticDoorWidth, Offset, 0.f);
	Close();
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlidingDoor::PostInitializeComponents()
{
	UpdateParameters();
	Super::PostInitializeComponents();
}
#if WITH_EDITOR 
void ASlidingDoor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	//if ((PropertyName == GET_MEMBER_NAME_CHECKED(ASlidingDoor, Offset)))
	//{
		UpdateParameters();
	//}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ASlidingDoor::UpdateParameters()
{
	DoorPositionClosed = FVector(-StaticDoorWidth, Offset, 0.f);
	DoorPositionOpened = FVector(0.0f, Offset, 0.f);
	if (bIsClosed)
	{
		DoorDynamic->SetRelativeLocation(DoorPositionClosed);
	}
	else
	{
		DoorDynamic->SetRelativeLocation(DoorPositionOpened);
	}
}

void ASlidingDoor::Close()
{
	bIsClosed = true;
	DoorDynamic->SetRelativeLocation(DoorPositionClosed);
}

void ASlidingDoor::Open()
{
	bIsClosed = false;
	DoorDynamic->SetRelativeLocation(DoorPositionOpened);
}

