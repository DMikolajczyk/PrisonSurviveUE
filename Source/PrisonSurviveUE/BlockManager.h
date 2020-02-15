// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellRoom.h"
#include "BlockManager.generated.h"

UCLASS()
class PRISONSURVIVEUE_API ABlockManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Cells")
	AActor* CellGroup;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OpenAllCells();
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void CloseAllCells();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Cells")
	TArray<ACellRoom*> Cells;

	
};
