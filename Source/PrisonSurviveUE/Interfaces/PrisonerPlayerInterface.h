// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PrisonerInterface.h"
#include "PrisonerPlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPrisonerPlayerInterface : public UPrisonerInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRISONSURVIVEUE_API IPrisonerPlayerInterface : public IPrisonerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	int TestX;
public:
};
