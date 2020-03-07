// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PersonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPersonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRISONSURVIVEUE_API IPersonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	float Health;
	int CashInBank;

public:
};