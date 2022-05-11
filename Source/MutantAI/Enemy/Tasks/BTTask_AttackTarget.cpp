// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackTarget.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackTarget::UBTTask_AttackTarget(){
	NodeName = TEXT("Attack Target");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMutantAIController* Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!Controller) EBTNodeResult::Failed;
	Controller->Attack();
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMutantAIController* Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!Controller) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	if (Controller->GetHasFinishedAttack()) {
		float CooldownTime = FMath::RandRange(AttackCooldown - RandomDiviation, AttackCooldown + RandomDiviation);
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
		if (Blackboard) {
			Blackboard->SetValueAsFloat(BlackboardKey.SelectedKeyName, CooldownTime);
		}
		Controller->SetHasFinishedAttack(false);
		Controller->SetCurrentState(EState::Hunting);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
