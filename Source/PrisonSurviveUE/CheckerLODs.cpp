
// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckerLODs.h"
#include "UObject/UObjectIterator.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACheckerLODs::ACheckerLODs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckerLODs::BeginPlay()
{
	Super::BeginPlay();
	PrintStaticMeshesWithoutLOD(0);
	
}

// Called every frame
void ACheckerLODs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckerLODs::PrintStaticMeshesWithoutLOD(int32 MinNumVertices)
{
	UE_LOG(LogTemp, Log, TEXT("Looking for StaticMeshes with 1 LOD..."));
	TArray<FString> StaticMeshesPaths;
	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(AActor::StaticClass()))
		{
			UStaticMeshComponent* StaticMeshComponent = Itr->FindComponentByClass<UStaticMeshComponent>();
			if (StaticMeshComponent)
			{
				UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
				if (StaticMesh)
				{
					const int32 NumberOfLODs = StaticMesh->GetNumLODs();
					const FString Path = StaticMesh->GetPathName();
					const int32 NumVertices = StaticMesh->GetNumVertices(0);
					if (NumberOfLODs <= 1 && !StaticMeshesPaths.Contains(Path) && NumVertices >= MinNumVertices && !StaticMeshLODSearchIgnore.Contains(Path))
					{
						UE_LOG(LogTemp, Log, TEXT("%s has       %d vertices"), *StaticMeshComponent->GetStaticMesh()->GetPathName(), NumVertices);
						StaticMeshesPaths.Add(Path);
					}
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %d StaticMeshes that meet criteria"), StaticMeshesPaths.Num());
}