// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInSight.h"

#include "../MutantAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerInSight::UBTService_PlayerInSight() {
	NodeName = TEXT("IsActorInSight");
	bNotifyBecomeRelevant = true;
}

uint16 UBTService_PlayerInSight::GetInstanceMemorySize() const
{
	return sizeof(FBTPlayerInSightMemory);
}

void UBTService_PlayerInSight::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	FBTPlayerInSightMemory* CurrentMemory = reinterpret_cast<FBTPlayerInSightMemory*>(NodeMemory);
	CurrentMemory->AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	CurrentMemory->ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
}


void UBTService_PlayerInSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FBTPlayerInSightMemory* CurrentMemory = reinterpret_cast<FBTPlayerInSightMemory*>(NodeMemory);
	if (!CurrentMemory->ControlledPawn) return;
	AActor* Target = CheckForTarget(NodeMemory, CurrentMemory);
	if (Target) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Target);
		if(CurrentMemory->AIController)	CurrentMemory->AIController->SetCurrentState(EState::Hunting);
		UE_LOG(LogTemp, Warning, TEXT("HUNGTING"));
	}
}

AActor* UBTService_PlayerInSight::CheckForTarget(uint8* NodeMemory, FBTPlayerInSightMemory* CurrentMemory)
{	
	FColor Color = FColor::Red;
	if (!CurrentMemory->AIController) return nullptr;

	FVector Start = CurrentMemory->ControlledPawn->GetActorLocation();
	FVector ForwardVector = CurrentMemory->ControlledPawn->GetActorForwardVector();

	AActor* Target = nullptr;
	for (AActor* Player : CurrentMemory->AIController->GetPlayers()) {
		FVector PlayerLocation = Player->GetActorLocation();
		FVector PlayerFacingVector = (PlayerLocation - Start).GetSafeNormal();
		float PlayerAngle = FMath::Abs(FMath::Acos(FVector::DotProduct(ForwardVector, PlayerFacingVector)));
		UE_LOG(LogTemp, Warning, TEXT("Player Angle: %f"), FMath::RadiansToDegrees(PlayerAngle));
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

