// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorStorage.generated.h"

UCLASS()
class MUTANTAI_API AActorStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorStorage();

	/**
	 * Sets up the instance of an ActorStorage. And stores every Actor of the PlayerClass in the Players array
	 * 
	 * \param World Pointer to the world
	 * \param PlayerClass The class that is used by all player instances
	 */
	void Setup(UWorld* World, TSubclassOf<AActor> PlayerClass);

	void AddEnemy(AActor* Enemy);

	void RemoveEnemy(AActor* Enemy);
	
	TArray<AActor*> GetPlayers() {
		return Players;
	}

	TArray<AActor*> GetEnemies() {
		return Enemies;
	}

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AActor*> Players;//All AActors of the specified player class

	UPROPERTY()
	TArray<AActor*> Enemies;

};
