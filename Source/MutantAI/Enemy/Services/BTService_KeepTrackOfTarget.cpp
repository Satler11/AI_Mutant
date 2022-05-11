// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_KeepTrackOfTarget.h"

#include "../MutantAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UBTService_KeepTrackOfTarget::UBTService_KeepTrackOfTarget(){
	NodeName = TEXT("Keep Track Of Target");
}

void UBTService_KeepTrackOfTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	AMutantAIController* Controller = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (Blackboard && ControlledPawn && Controller) {
		AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
		if (!Target) return;
		FHitResult HitResult;
		TArray<AActor*> ActorsToIgnore = Controller->GetAllEnemies();
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), ControlledPawn->GetActorLocation(), Target->GetActorLocation(), UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true)) {
			if (HitResult.GetActor() == Target) {
				Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, Target->GetActorLocation());
			}
			else {
				Blackboard->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
				Controller->SetCurrentState(EState::Inspecting);
			}
		}
	}

}
