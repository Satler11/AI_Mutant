// Copyright Epic Games, Inc. All Rights Reserved.


#include "MutantAIGameModeBase.h"

#include "General/ActorStorage.h"

AActorStorage* AMutantAIGameModeBase::GetActorStorage()
{
	if (!ActorStorage) {
		ActorStorage = NewObject<AActorStorage>();
		UE_LOG(LogTemp, Warning, TEXT("Class: %s"), *PlayerClass.Get()->GetFullName());
		ActorStorage->Setup(GetWorld(), PlayerClass);
		UE_LOG(LogTemp, Warning, TEXT("Created Actor Storage"));
	}
	return ActorStorage;
}
