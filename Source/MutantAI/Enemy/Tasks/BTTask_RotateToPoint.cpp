// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToPoint.h"

#include "../MutantAIController.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_RotateToPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;
	ControlledPawn = Controller->GetPawn();
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!ControlledPawn || !Blackboard) return EBTNodeResult::Failed;
	Alpha = 0;
	StartRotation = ControlledPawn->GetActorRotation().Quaternion();
	FVector StartForwardVector = ControlledPawn->GetActorForwardVector();
	FQuat StartForwardRotation = StartForwardVector.Rotation().Quaternion();
	FVector TargetLocation = Blackboard->GetValueAsVector(BlackboardKey.SelectedKeyName);
	FVector PawnLocation = ControlledPawn->GetActorLocation();
	FVector EndForwardVector = (TargetLocation - PawnLocation).GetSafeNormal();
	EndRotation = EndForwardVector.Rotation().Quaternion();
	if (FVector::DotProduct(StartForwardVector, EndForwardVector) > 0) Controller->SetIsTurningRight(true);
	else Controller->SetIsTurningLeft(true);
	
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Alpha += RotationSpeed * DeltaSeconds;
	UE_LOG(LogTemp, Warning, TEXT("Alpha: %f"), Alpha);
	FQuat CurrentRotation =FQuat::Slerp(StartRotation, EndRotation, Alpha);
	ControlledPawn->SetActorRotation(CurrentRotation);

	if (Alpha >= 1) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Controller->SetIsTurningLeft(false);
		Controller->SetIsTurningRight(false);
		UE_LOG(LogTemp, Warning, TEXT("Finished"));
	}
}
