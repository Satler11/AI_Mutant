// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorStorage.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AActorStorage::AActorStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AActorStorage::Setup(UWorld* World, TSubclassOf<AActor> PlayerClass)
{
	if (PlayerClass.Get() && World) {
		UGameplayStatics::GetAllActorsOfClass(World, PlayerClass, Players);
		UE_LOG(LogTemp, Warning, TEXT("Number of Players: %d"), Players.Num());
	}
}

// Called when the game starts or when spawned
void AActorStorage::BeginPlay()
{
	Super::BeginPlay();
	
}
