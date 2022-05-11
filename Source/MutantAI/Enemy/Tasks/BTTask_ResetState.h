// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ResetState.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTTask_ResetState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ResetState();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
