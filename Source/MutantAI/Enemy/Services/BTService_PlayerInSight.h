// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerInSight.generated.h"


UCLASS()
class MUTANTAI_API UBTService_PlayerInSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlayerClass;//The class that is used by the player

	UPROPERTY(EditAnywhere)
	float Distance; //How far the AI can see

	UPROPERTY(EditAnywhere)
	float ViewConeAngle;//The angle of the view cone

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;//If view cone should be visualized

	UBTService_PlayerInSight();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	/**
	 * Checks if an AActor of type PlayerClass is in sight of the AI
	 * 
	 * \param NodeMemory the original node memory
	 * \param CurrentMemory original node memory converted to FBTPlayerInSightMemory
	 * \return 
	 */
	AActor* CheckForTarget(uint8* NodeMemory, class AMutantAIController* AIController, APawn* ControlledPawn);

};
