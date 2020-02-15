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
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *CellGroup->GetFullName());

	TArray<AActor*> CellsTmp;
	CellGroup->GetAttachedActors(/*out*/ CellsTmp);

	for (AActor* Cell : CellsTmp)
	{
		ACellRoom* CellTmp = Cast<ACellRoom>(Cell);
		if (CellTmp != NULL)
		{
			Cells.Add(CellTmp);
		}
	}
	CloseAllCells();
	
}


// Called every frame
void ABlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockManager::OpenAllCells() {
	for (ACellRoom* Cell : Cells)
	{
		if (Cell->Door != NULL)
		{
			Cell->Door->Open();
			UE_LOG(LogTemp, Warning, TEXT("Cell number %d has opened."), Cell->GetCellID());
		}
				
	}
}

void ABlockManager::CloseAllCells() {
	for (ACellRoom* Cell : Cells)
	{
		if (Cell->Door != NULL)
		{
			Cell->Door->Close();
			UE_LOG(LogTemp, Warning, TEXT("Cell number %d has closed."), Cell->GetCellID());
		}

	}
}