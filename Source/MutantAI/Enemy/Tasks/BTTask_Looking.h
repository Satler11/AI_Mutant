// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Looking.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTTask_Looking : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


public:

	UBTTask_Looking();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float Duration = 0.0f;

	UPROPERTY(EditAnywhere)
	float RandomDivation = 0.0f;

private:
	float LookTime = 0.0f;

	float TimePassed = 0.0f;

	class AMutantAIController* MyController;
};