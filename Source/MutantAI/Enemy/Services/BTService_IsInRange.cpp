// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsInRange.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_IsInRange::UBTService_IsInRange(){
	NodeName = TEXT("IsActorInRange?");
}

void UBTService_IsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMutantAIController* AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	ACharacter* ControlledCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard || !AIController || !ControlledCharacter) return;
	if (IsActorInRange(OwnerComp, NodeMemory, Blackboard, AIController, ControlledCharacter)) {
		Blackboard->SetValueAsBool(IsInRangeKey.SelectedKeyName, true);
	}
	else {
		Blackboard->SetValueAsBool(IsInRangeKey.SelectedKeyName, false);
	}
}

bool UBTService_IsInRange::IsActorInRange(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UBlackboardComponent* Blackboard, AMutantAIController* AIController, ACharacter* ControlledCharacter)
{
	FVector TraceStart = ControlledCharacter->GetActorLocation();
	TraceStart += ControlledCharacter->GetActorForwardVector() * SphereTraceOffset;
	FVector TraceEnd = TraceStart;
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	if (bDrawDebug) UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceEnd, Range, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, GetNextTickRemainingTime(NodeMemory));
	else UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceEnd, Range, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);
	bool bTargetInRange = false;
	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
	for (FHitResult HitResult : HitResults) {
		if (HitResult.bBlockingHit && TargetActor && HitResult.GetActor() == TargetActor) {
			bTargetInRange = true;
		}
	}
	
	return bTargetInRange;
}
