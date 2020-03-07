// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PersonInterface.h"
#include "PrisonerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPrisonerInterface : public UPersonInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRISONSURVIVEUE_API IPrisonerInterface : public IPersonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	int Cigarettes;
	float Eatfull;
	float Respect;
	float Energy;
	float Comfort;
	// Gang GangType;
	int CellID;
	float SocialHappines;
	// PrisonerRelation[] Relations;
	float ToiletDefecation;
	float Clean;
	bool bHasTopBed;

public:
};
