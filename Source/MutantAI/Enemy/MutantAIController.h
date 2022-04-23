// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MutantAIController.generated.h"

UENUM(BlueprintType)
enum EState {
	Wandering UMETA(DisplayName = "Wandering"),
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

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	EState CurrentState = EState::Wandering;

	bool bIsTurningLeft = false;
	bool bIsTurningRight = false;

	class AMutantCharacter* MutantCharacter;

	
};
