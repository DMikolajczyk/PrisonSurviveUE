// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockManager.h"


// Sets default values
ABlockManager::ABlockManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ABlockManager::BeginPlay()
{
	// P�niej mo�e zrobi� z tego singleton wi�c poni�ej sprawdzenie adresu �eby zobaczy� czy b�dzie jedna referencja
	UE_LOG(LogTemp, Warning, TEXT("Test of address: %d"), this);

	Super::BeginPlay();
	TArray<AActor*> CellsTmp;
	CellGroup->GetAttachedActors(CellsTmp);

	for (AActor* Cell : CellsTmp)					/// Tu wywala jaki� b��d?
	{
		ACellRoom* CellTmp = Cast<ACellRoom>(Cell);
		if (CellTmp != NULL)
		{
			Cells.Add(CellTmp);
		}
	}
	OpenAllCells();
}


// Called every frame
void ABlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockManager::OpenAllCells() 
{
	for (ACellRoom* Cell : Cells)
	{
		if (Cell->Door != NULL)
		{
			Cell->Door->Open();
		}
				
	}
	bIsBlockOpen = true;
}

void ABlockManager::CloseAllCells() 
{
	for (ACellRoom* Cell : Cells)
	{
		if (Cell->Door != NULL)
		{
			Cell->Door->Close();
		}

	}
	bIsBlockOpen = false;
}

void ABlockManager::RevertStateOfOpenCell() 
{
	for (ACellRoom* Cell : Cells)
	{
		if (Cell->Door != NULL)
		{
			//if (bIsBlockOpen == Cell->Door->bIsOpen)
			if (bIsBlockOpen == Cell->Door->GetIsOpen())
			{
				Cell->Door->ToggleDoor();
			}
		}

	}
	bIsBlockOpen = !bIsBlockOpen;
}
