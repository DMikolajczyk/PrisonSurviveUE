// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickable.h"

// Sets default values
AItemPickable::AItemPickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	Name = TEXT("None");
}

// Called when the game starts or when spawned
void AItemPickable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("deltaTime: %f"), DeltaTime);
}

void AItemPickable::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("You did action on object: %s"), *Name);
}