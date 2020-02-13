// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorStatic = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door static"));
	DoorDynamic = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door dynamic"));
	Offset = 9.f;
	DoorPositionOpened = FVector(0.f, Offset, 0.f);
	DoorPositionClosed = FVector(0.f, Offset, 0.f);
	

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
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ASlidingDoor, Offset)))
	{
		UpdateParameters();
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ASlidingDoor::UpdateParameters()
{
	StaticDoorWidth = DoorStatic->Bounds.GetBox().GetSize().X;
	DoorPositionClosed = FVector(-StaticDoorWidth, Offset, 0.f);
	DoorPositionOpened = FVector(0.0f, Offset, 0.f);
	DoorDynamic->SetRelativeLocation(DoorPositionClosed);
	UE_LOG(LogTemp, Warning, TEXT("Door width: %f"), StaticDoorWidth);
}