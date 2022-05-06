// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Looking.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_Looking::UBTTask_Looking() {
	NodeName = TEXT("Looking");
	bNotifyTick = true;
}

uint16 UBTTask_Looking::GetInstanceMemorySize() const
{
	return sizeof(FBTLookingMemory);
}

EBTNodeResult::Type UBTTask_Looking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FBTLookingMemory* CurrentMemory = reinterpret_cast<FBTLookingMemory*>(NodeMemory);

	float CurrentLookTime = FMath::RandRange(Duration - RandomDiviation, Duration + RandomDiviation);
	CurrentMemory->LookTime = CurrentLookTime > 0 ? CurrentLookTime : 0;
	return EBTNodeResult::InProgress;
}

void UBTTask_Looking::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	FBTLookingMemory* CurrentMemory = reinterpret_cast<FBTLookingMemory*>(NodeMemory);
	CurrentMemory->TimePassed += DeltaSeconds;
	if (CurrentMemory->TimePassed >= CurrentMemory->LookTime) {
		CurrentMemory->TimePassed = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

