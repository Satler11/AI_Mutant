// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToPoint.h"

#include "../MutantAIController.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToPoint::UBTTask_RotateToPoint() {
	NodeName = TEXT("Rotate to point");
	bNotifyTick = true;
}

uint16 UBTTask_RotateToPoint::GetInstanceMemorySize() const
{
	return sizeof(FBTRotateToPointMemory);
}

EBTNodeResult::Type UBTTask_RotateToPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FBTRotateToPointMemory* CurrentMemory = reinterpret_cast<FBTRotateToPointMemory*>(NodeMemory);

	CurrentMemory->Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (!CurrentMemory->Controller) return EBTNodeResult::Failed;
	CurrentMemory->ControlledPawn = CurrentMemory->Controller->GetPawn();
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!CurrentMemory->ControlledPawn || !Blackboard) return EBTNodeResult::Failed;
	CurrentMemory->Alpha = 0;
	CurrentMemory->CurrentRotationSpeed = FMath::RandRange(RotationSpeed - RandomDivation, RotationSpeed + RandomDivation);

	CurrentMemory->StartRotation = CurrentMemory->ControlledPawn->GetActorRotation().Quaternion();
	FVector StartForwardVector = CurrentMemory->ControlledPawn->GetActorForwardVector();
	FQuat StartForwardRotation = StartForwardVector.Rotation().Quaternion();
	FVector TargetLocation = Blackboard->GetValueAsVector(BlackboardKey.SelectedKeyName);
	FVector PawnLocation = CurrentMemory->ControlledPawn->GetActorLocation();
	FVector EndForwardVector = (TargetLocation - PawnLocation).GetSafeNormal();
	CurrentMemory->EndRotation = EndForwardVector.Rotation().Quaternion();
	if (FVector::DotProduct(StartForwardVector, EndForwardVector) > 0) CurrentMemory->Controller->SetIsTurningRight(true);
	else CurrentMemory->Controller->SetIsTurningLeft(true);
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	FBTRotateToPointMemory* CurrentMemory = reinterpret_cast<FBTRotateToPointMemory*>(NodeMemory);
	CurrentMemory->Alpha += (1/ CurrentMemory->CurrentRotationSpeed) * DeltaSeconds;
	FQuat CurrentRotation =FQuat::Slerp(CurrentMemory->StartRotation, CurrentMemory->EndRotation, CurrentMemory->Alpha);
	CurrentMemory->ControlledPawn->SetActorRotation(CurrentRotation);

	if (CurrentMemory->Alpha >= 1) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		CurrentMemory->Controller->SetIsTurningLeft(false);
		CurrentMemory->Controller->SetIsTurningRight(false);
	}
}
