// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsInRange.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_IsInRange::UBTService_IsInRange(){
	NodeName = TEXT("IsActorInRange?");
	bNotifyBecomeRelevant = true;
}

uint16 UBTService_IsInRange::GetInstanceMemorySize() const
{
	return sizeof(FBTIsInRangeMemory);
}

void UBTService_IsInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTIsInRangeMemory* CurrentMemory = reinterpret_cast<FBTIsInRangeMemory*>(NodeMemory);
	CurrentMemory->AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	CurrentMemory->ControlledCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
}

void UBTService_IsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTIsInRangeMemory* CurrentMemory = reinterpret_cast<FBTIsInRangeMemory*>(NodeMemory);
	if (IsActorInRange(OwnerComp, NodeMemory, CurrentMemory) && CurrentMemory->AIController) {
		CurrentMemory->AIController->SetCurrentState(EState::Attacking);
	}
}

bool UBTService_IsInRange::IsActorInRange(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FBTIsInRangeMemory* CurrentMemory)
{
	if (!CurrentMemory->ControlledCharacter) return false;
	FVector TraceStart = CurrentMemory->ControlledCharacter->GetActorLocation();
	TraceStart += CurrentMemory->ControlledCharacter->GetActorForwardVector() * SphereTraceOffset;
	FVector TraceEnd = TraceStart;
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	if (bDrawDebug) UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceEnd, Range, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, GetNextTickRemainingTime(NodeMemory));
	else UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceEnd, Range, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);
	bool bTargetInRange = false;
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) {
		AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
		for (FHitResult HitResult : HitResults) {
			if (HitResult.bBlockingHit && TargetActor && HitResult.GetActor() == TargetActor) {
				bTargetInRange = true;
			}
		}
	}
	return bTargetInRange;
}
