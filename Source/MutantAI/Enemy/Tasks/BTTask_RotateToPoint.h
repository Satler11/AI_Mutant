// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotateToPoint.generated.h"

struct FBTRotateToPointMemory {
	FQuat StartRotation;
	FQuat EndRotation;

	class APawn* ControlledPawn;
	class AMutantAIController* Controller;
	
	float Alpha;
	float CurrentRotationSpeed;
};


UCLASS()
class MUTANTAI_API UBTTask_RotateToPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float RandomDivation = 0.0f;

	UBTTask_RotateToPoint();

	uint16 GetInstanceMemorySize() const override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
