// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MutantAIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MUTANTAI_API AMutantAIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**
	 * Creates a new AActorStorage instance or provides a pointer to the existing one stored in ActorStorage.
	 * 
	 * /return the pointer to the AActorStorage instance.
	 */
	class AActorStorage* GetActorStorage();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PlayerClass;//The class that is used by all player instances

	UPROPERTY()
	class AActorStorage* ActorStorage;

	
};
