// Fill out your copyright notice in the Description page of Project Settings.


#include "CellRoom.h"

// Sets default values
ACellRoom::ACellRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cell_ID = 0;
}

int ACellRoom::GetCellID()
{
	return Cell_ID;
}

void ACellRoom::SetCellID(int Number)
{
	Cell_ID = Number;
}

// Called when the game starts or when spawned
void ACellRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

