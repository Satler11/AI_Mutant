// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsInRange.generated.h"

struct FBTIsInRangeMemory {
	class AMutantAIController* AIController; //The AIController of the AI instance
	class ACharacter* ControlledCharacter; //The Character that is controlled by the AI instance
};

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTService_IsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IsInRange();

	uint16 GetInstanceMemorySize() const override;

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float Range; //The range in which the player is in reach

	UPROPERTY(EditAnywhere)
	float SphereTraceOffset;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;//If view cone should be visualized

private: 

	bool IsActorInRange(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FBTIsInRangeMemory* CurrentMemory);
};
