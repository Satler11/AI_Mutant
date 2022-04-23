// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Looking.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_Looking::UBTTask_Looking() {
	NodeName = TEXT("Looking");
}

EBTNodeResult::Type UBTTask_Looking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!MyController) return EBTNodeResult::Failed;

	float Random = FMath::RandRange(0.0f, RandomDivation);
	int Sign = FMath::Sign(FMath::RandRange(-1.0f, 1.0f));
	LookTime = Duration - Sign * Random;
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_Looking::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	TimePassed += DeltaSeconds;
	if (TimePassed >= LookTime) {
		TimePassed = 0.0f;
		if (!MyController) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

