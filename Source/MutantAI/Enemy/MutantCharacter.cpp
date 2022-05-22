// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantCharacter.h"

#include "MutantAIController.h"
#include "../General/HealthComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMutantCharacter::AMutantCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}
// Called when the game starts or when spawned
void AMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AMutantCharacter::HandleDamage);
	
}

void AMutantCharacter::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	HealthComponent->ReduceHealth(int(Damage));
	if (HealthComponent->GetCurrentHealth() <= 0) {
		AMutantAIController* MyController = Cast<AMutantAIController>(GetController());
		if (MyController) MyController->SetCurrentState(EState::Dying);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		GetCharacterMovement()->SetAvoidanceEnabled(false);
	}
	else {
		PlayGetHitMontage();
		AMutantAIController* MyController = Cast<AMutantAIController>(GetController());
		if (MyController) MyController->HandleHit(DamageCauser);
	}
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
	else if (NewState == EState::Hunting || NewState == EState::Tracking || NewState == EState::Inspecting) {
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = HuntingSpeed;
	}
	else if (NewState == EState::Attacking) {
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = AttackingSpeed;
	}
	else if (NewState == EState::Dying) {
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = 0;
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

void AMutantCharacter::PlayAttackMontage_Implementation() {
	//Implementation in blueprint
}


void AMutantCharacter::PlayGetHitMontage_Implementation() {
	//Implementation in blueprint
}

void AMutantCharacter::OnAttackMontageEnd()
{
	bIsPlayingAttackMontage = false;
	AMutantAIController* AIController = Cast<AMutantAIController>(GetController());
	if (AIController) {
		AIController->SetHasFinishedAttack(true);
	}
}


