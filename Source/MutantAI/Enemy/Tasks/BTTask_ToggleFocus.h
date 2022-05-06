// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ToggleFocus.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTTask_ToggleFocus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ToggleFocus();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	bool bEnableFocus; //If focus should be set or not
	
};
