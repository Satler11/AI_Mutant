// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMutantCharacter::AMutantCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void AMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMutantCharacter::ChangeSpeed(EState NewState)
{
	if (NewState == EState::Wandering) {
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = WanderingSpeed;
	}
	else if (NewState == EState::Hunting) {
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = HuntingSpeed;
	}
}

void AMutantCharacter::PlayTurnMontage_Implementation(bool bIsTurningLeft)
{
	//Implementation in blueprint
}

void AMutantCharacter::StopTurnMontage_Implementation(bool bIsTurningLeft)
{
	//Implementation in blueprint
}


