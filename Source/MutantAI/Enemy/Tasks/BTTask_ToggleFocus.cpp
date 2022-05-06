// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ToggleFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ToggleFocus::UBTTask_ToggleFocus(){
	NodeName = TEXT("ToggleFocus");
}

EBTNodeResult::Type UBTTask_ToggleFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bEnableFocus) {
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();;
		if (!Blackboard) return EBTNodeResult::Failed;
		AActor* ActorToFocus = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
		OwnerComp.GetAIOwner()->SetFocus(ActorToFocus, EAIFocusPriority::Gameplay);
	}
	else {
		OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
	}
	return EBTNodeResult::Succeeded;
}
