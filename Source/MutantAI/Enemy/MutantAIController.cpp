// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantAIController.h"

#include "MutantCharacter.h"
#include "../General/ActorStorage.h"
#include "../MutantAIGameModeBase.h"

#include "BehaviorTree/BlackboardComponent.h"

void AMutantAIController::SetCurrentState(EState NewState)
{
	CurrentState = NewState;
	if (Blackboard) {
		Blackboard->SetValueAsEnum(TEXT("CurrentState"), CurrentState);
	}
	if(MutantCharacter)	MutantCharacter->ChangeSpeed(NewState);
}

TArray<AActor*> AMutantAIController::GetPlayers()
{
	if (ActorStorage) {
		return ActorStorage->GetPlayers();
	}
	return {};
}

void AMutantAIController::BeginPlay() {
	Super::BeginPlay();
	if (BehaviorTree) {
		RunBehaviorTree(BehaviorTree);
	}
	MutantCharacter = Cast<AMutantCharacter>(GetPawn());
	AMutantAIGameModeBase* GameMode = Cast<AMutantAIGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		ActorStorage = GameMode->GetActorStorage();
	}
	
}

void AMutantAIController::SetIsTurningRight(bool bIsTurningRight_In) {
	if (bIsTurningRight && !bIsTurningRight_In && MutantCharacter)
		MutantCharacter->StopTurnMontage(false);
	else if (bIsTurningRight_In && MutantCharacter)
		MutantCharacter->PlayTurnMontage(false);
	bIsTurningRight = bIsTurningRight_In;
}

void AMutantAIController::SetIsTurningLeft(bool bIsTurningLeft_In) {
	if (bIsTurningLeft && !bIsTurningLeft_In && MutantCharacter)
		MutantCharacter->StopTurnMontage(true);
	else if (bIsTurningLeft_In && MutantCharacter)
		MutantCharacter->PlayTurnMontage(true);

	bIsTurningLeft = bIsTurningLeft_In;
}

