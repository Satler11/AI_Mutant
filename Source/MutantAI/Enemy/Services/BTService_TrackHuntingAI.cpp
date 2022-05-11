// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TrackHuntingAI.h"

#include "../MutantAIController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_TrackHuntingAI::UBTService_TrackHuntingAI(){
	NodeName = TEXT("Track Hunting AIs");
}

void UBTService_TrackHuntingAI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMutantAIController* AIController = Cast<AMutantAIController>(OwnerComp.GetAIOwner());
	if (AIController) {
		APawn* ControlledPawn = AIController->GetPawn();
		TArray<AActor*> Enemies = AIController->GetAllEnemies();
		AActor* ClosestEnemy = nullptr;
		float SmallestDistance = ViewDistance + 1;
		FVector CurrentLocation = ControlledPawn->GetActorLocation();
		for (AActor* Enemy : Enemies) {
			if (Enemy == ControlledPawn) continue;
			AMutantAIController* OtherController = Cast<AMutantAIController>(Enemy->GetOwner());
			if (!OtherController || OtherController->GetCurrentState() != EState::Hunting) continue;
			FVector OtherLocation = Enemy->GetActorLocation();
			FVector OtherDirection = OtherLocation - CurrentLocation;
			float CurrentDistance = FMath::Abs((OtherDirection).Length());
			if (CurrentDistance < SmallestDistance) {
				FVector OtherDirectionNormalized = OtherDirection.GetSafeNormal();
				float ActorAngle = FMath::Abs(FMath::Acos(FVector::DotProduct(ControlledPawn->GetActorForwardVector(), OtherDirectionNormalized)));
				if (ViewConeAngle > FMath::RadiansToDegrees(ActorAngle)) {
					FHitResult HitResult;
					TArray<AActor*> ActorsToIgnore;
					ActorsToIgnore.Add(ControlledPawn);
					if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), CurrentLocation, OtherLocation, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true)) {
						SmallestDistance = CurrentDistance;
						ClosestEnemy = Enemy;
					}
				}
			}
		}
		FColor Color = FColor::Red;
		if (SmallestDistance < ViewDistance + 1) {
			UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
			if (Blackboard) {
				Blackboard->SetValueAsObject(TargetKey.SelectedKeyName, ClosestEnemy);
				AIController->SetCurrentState(EState::Tracking);
				Color = FColor::Green;
			}
		}
		if (bDrawDebug) {
			DrawDebugCone(GetWorld(), ControlledPawn->GetActorLocation(), ControlledPawn->GetActorForwardVector(), ViewDistance, FMath::DegreesToRadians(ViewConeAngle), FMath::DegreesToRadians(ViewConeAngle), 12, Color, false, GetNextTickRemainingTime(NodeMemory), 0, 3);
		}
	}

}

