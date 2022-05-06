// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotateToPoint.generated.h"

struct FBTRotateToPointMemory {
	FQuat StartRotation;  //The inital rotation
	FQuat EndRotation;	//Rotation at the end of the task

	class APawn* ControlledPawn; //The Pawn that is controlled by the AI instance
	class AMutantAIController* Controller; //The AI controller of this AI instance
	
	float Alpha; //The current value of alpha (interpolation between StartRotation and EndRotation)
	float CurrentRotationSpeed; //How fast the AI rotates
};


UCLASS()
class MUTANTAI_API UBTTask_RotateToPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float RotationSpeed; //How fast the AI rotates

	UPROPERTY(EditAnywhere)
	float RandomDiviation = 0.0f; //Random Diviation for the rotation speed

	UBTTask_RotateToPoint();

	uint16 GetInstanceMemorySize() const override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	/**
	 * Initializes all values for the rotation.
	 *
	 * \param OwnerComp
	 * \param CurrentMemory the original node memory converted to FBTRotateToPointMemory
	 * \return EBTNodeResult::InProgress if successful, EBTNodeResult::Failed otherwise
	 */
	EBTNodeResult::Type InitializeRotation(UBehaviorTreeComponent& OwnerComp, FBTRotateToPointMemory* CurrentMemory);
};
