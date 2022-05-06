// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MutantAIController.generated.h"

UENUM(BlueprintType)
enum EState {
	Wandering	UMETA(DisplayName = "Wandering"),
	Hunting		UMETA(DisplayName = "Hunting"),
	Attacking	UMETA(DisplayName = "Attacking"),
};
/**
 * 
 */
UCLASS()
class MUTANTAI_API AMutantAIController : public AAIController
{
	GENERATED_BODY()

public:
	void SetCurrentState(EState NewState);

	UFUNCTION(BlueprintCallable)
	bool GetIsTurningRight() {
		return bIsTurningRight;
	}

	void SetIsTurningRight(bool bIsTurningRight_In);

	UFUNCTION(BlueprintCallable)
	bool GetIsTurningLeft() {
		return bIsTurningLeft;
	}

	void SetIsTurningLeft(bool bIsTurningLeft_In);

	UFUNCTION(BlueprintCallable)
	EState GetCurrentState() {	return CurrentState; }

	/**
	 * Returns all currently available players.
	 * 
	 * \return TArray with all AActors of the defined player class in the GameMode
	 */
	TArray<AActor*> GetPlayers();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	EState CurrentState = EState::Wandering;//The current state of the AI

	bool bIsTurningLeft = false;//If the character is turning to the left
	bool bIsTurningRight = false;//If the character is turning to the right

	UPROPERTY()
	class AMutantCharacter* MutantCharacter;//The controlled Character

	UPROPERTY()
	class AActorStorage* ActorStorage;

	
};
