// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_TrackHuntingAI.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API UBTService_TrackHuntingAI : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_TrackHuntingAI();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere)
	float ViewConeAngle;

	UPROPERTY(EditAnywhere)
	float ViewDistance;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;

};
