// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PrisonerControllerAI.generated.h"

/**
 * 
 */
UCLASS()
class PRISONSURVIVEUE_API APrisonerControllerAI : public AAIController
{
	GENERATED_BODY()

public:
	APrisonerControllerAI(const FObjectInitializer& ObjInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;
	
	/**Execute when AI spot or lost any pawn*/
	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*> &DetectedPawns);
		
	/**How far AI character can spot anything*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI parameters")
	float SightRadius;

	/**How long save last point where AI spotted other character [seconds]*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI parameters")
	float SightAge;

	/**Distance from spotting border, where AI lost other character after spot (0 is equal to "Sight Radius")*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI parameters")
	float LoseSightRadius;

	/**Field of view where AI can spot other characters*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI parameters")
	float FieldOfView;

	UPROPERTY(EditAnywhere)
	float DistanceOffsetToTarget;

	UPROPERTY(VisibleAnywhere)
	AActor* TargetedCharacter;

	/**Object which handle parameters for spotting*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI parameters")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	class APrisonerCharacterAI* PrisonerAI;

	UPROPERTY()
	TArray <AActor*> ActorsInRange;

	UPROPERTY()
	TArray <float> test;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* GetBlackboardComponent() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComp;

	class UBlackboardComponent* BlackboardComp;

};
