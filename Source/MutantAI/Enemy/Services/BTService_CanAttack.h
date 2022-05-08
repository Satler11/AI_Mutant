// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTService_CanAttack : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_CanAttack();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsInRangeKey;

};
