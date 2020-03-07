// Fill out your copyright notice in the Description page of Project Settings.


#include "Waypoint.h"
#include "PrisonerCharacterAI.h"

// Sets default values
AWaypoint::AWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnCharacterEnter);

	/// Random NextWayPoint
}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaypoint::OnCharacterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APrisonerCharacterAI* PrisonerAI = nullptr;
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		PrisonerAI = Cast<APrisonerCharacterAI>(OtherActor);
		if (PrisonerAI != nullptr)
		{
			PrisonerAI->NextWaypoint = NextWayPoint;
		}
		
	}
}


