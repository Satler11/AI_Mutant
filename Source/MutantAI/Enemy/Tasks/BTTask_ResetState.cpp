// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ResetState.h"

#include "../MutantAIController.h"

UBTTask_ResetState::UBTTask_ResetState(){
	NodeName = TEXT("ResetState");
}

EBTNodeResult::Type UBTTask_ResetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMutantAIController* Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;
	Controller->SetCurrentState(EState::Wandering);
	return EBTNodeResult::Succeeded;
}
