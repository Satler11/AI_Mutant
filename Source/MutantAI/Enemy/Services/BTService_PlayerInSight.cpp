// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInSight.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerInSight::UBTService_PlayerInSight() {
	NodeName = TEXT("IsActorInSight");
}


void UBTService_PlayerInSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMutantAIController* AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn || !AIController) return;
	AActor* Target = CheckForTarget(NodeMemory, AIController, ControlledPawn);
	if (Target) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Target);
		AIController->SetCurrentState(EState::Hunting);
	}
}

AActor* UBTService_PlayerInSight::CheckForTarget(uint8* NodeMemory, AMutantAIController* AIController, APawn* ControlledPawn)
{	
	FColor Color = FColor::Red;
	FVector Start =ControlledPawn->GetActorLocation();
	FVector ForwardVector = ControlledPawn->GetActorForwardVector();

	AActor* Target = nullptr;
	for (AActor* Player : AIController->GetPlayers()) {
		FVector PlayerLocation = Player->GetActorLocation();
		FVector PlayerFacingVector = (PlayerLocation - Start).GetSafeNormal();
		float PlayerAngle = FMath::Abs(FMath::Acos(FVector::DotProduct(ForwardVector, PlayerFacingVector)));
		if (FMath::RadiansToDegrees(PlayerAngle) > ViewConeAngle) continue;
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start + PlayerFacingVector * 40, Start + PlayerFacingVector * Distance, ECollisionChannel::ECC_Camera);
		if (bHit && HitResult.GetActor()->IsA(PlayerClass)) {
			Color = FColor::Green;
			Start = Start + PlayerFacingVector * 40;
			Target = Player;
			break;
		}
	}

	if (bDrawDebug) {
		DrawDebugCone(GetWorld(), Start, ForwardVector, Distance, FMath::DegreesToRadians(ViewConeAngle), FMath::DegreesToRadians(ViewConeAngle), 12, Color, false, GetNextTickRemainingTime(NodeMemory), 0, 3);
	}
	return Target;
}

