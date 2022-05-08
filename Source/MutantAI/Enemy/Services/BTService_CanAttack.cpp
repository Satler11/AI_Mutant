// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CanAttack.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_CanAttack::UBTService_CanAttack(){
	NodeName = TEXT("Can Attack?");
}


void UBTService_CanAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		float AttackCooldownTime = Blackboard->GetValueAsFloat(BlackboardKey.SelectedKeyName);
		if (AttackCooldownTime <= 0 && Blackboard->GetValueAsBool(IsInRangeKey.SelectedKeyName)) {
			AMutantAIController* AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
			if (AIController) {
				AIController->SetCurrentState(EState::Attacking);
			}
		}
		AttackCooldownTime -= DeltaSeconds;
		Blackboard->SetValueAsFloat(BlackboardKey.SelectedKeyName, AttackCooldownTime);
	}
}
