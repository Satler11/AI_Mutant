// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotateToPoint.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTTask_RotateToPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	class APawn* ControlledPawn;

	UPROPERTY()
	class AMutantAIController* Controller;

	UPROPERTY()
	FQuat EndRotation;

	UPROPERTY()
	FQuat StartRotation;

	UPROPERTY()
	float Alpha;

};
