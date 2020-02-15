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
	DoorDynamic->SetRelativeLocation(DoorPositionOpened);
	bIsOpen = true;

}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("ControlDoor"));
		Timeline.AddInterpFloat(DoorCurve, TimelineProgress);
		
		/* Funkcja SetState by³aby odpalana w momencie zakoñczenia animacji.
		FOnTimelineEventStatic TimelineFinishedCallback;
		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));
		Timeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
		*/
	}
}

// Called every frame
void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);

}

void ASlidingDoor::PostInitializeComponents()
{
	UpdateParameters();
	Super::PostInitializeComponents();
}
#if WITH_EDITOR 
void ASlidingDoor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateParameters();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ASlidingDoor::UpdateParameters()
{
	DoorPositionOpened = FVector(0.f, Offset, 0.f);
	DoorDynamic->SetRelativeLocation(DoorPositionOpened);
}

void ASlidingDoor::Close()
{
	if (bIsOpen)
	{
		ToggleDoor();
	}
}

void ASlidingDoor::Open()
{
	if (!bIsOpen)
	{
		ToggleDoor();
	}
}

void ASlidingDoor::ControlDoor()
{
	// Playback position daje nam informacjê w której czêœci animacji jesteœmy w wartoœci 0-1
	PlaybackPosition = Timeline.GetPlaybackPosition();
	CurveFloatValue = DoorCurve->GetFloatValue(PlaybackPosition) * StaticDoorWidth;
	
	DoorDynamic->SetRelativeLocation(FVector(-CurveFloatValue, Offset, 0.0f));
}

void ASlidingDoor::ToggleDoor()
{
	bIsOpen = !bIsOpen;
	if (bIsOpen) 
	{
		Timeline.Reverse();
	}
	else 
	{
		Timeline.Play();
	}
	
}

bool ASlidingDoor::GetIsOpen() 
{
	return bIsOpen;
}

void ASlidingDoor::SetIsOpen(bool open) 
{
	bIsOpen = open;
}
