// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetMesh(), FName(TEXT("CameraSocket")));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GunAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GunAudioComponent"));
	GunAudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("CameraSocket")));
	
}
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsFiring) {
		Shoot();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleFiring);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &APlayerCharacter::ToggleFiring);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleAiming);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &APlayerCharacter::ToggleAiming);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);

}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::ToggleFiring()
{
	bIsFiring = !bIsFiring;
}

void APlayerCharacter::ToggleAiming()
{
	bIsAiming = !bIsAiming;
	if (bIsAiming) StartAiming();
	else StopAiming();
}

void APlayerCharacter::Shoot()
{
	if (bCanFire) {
		PlayFiringMontage();
		FHitResult HitResult;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		bool bHasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraComponent->GetComponentLocation(), CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * ShootingDistance,
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
		if (bHasHit) {
			ACharacter* Character = Cast<ACharacter>(HitResult.GetActor());
			if (Character) Character->TakeDamage(10, FDamageEvent(), nullptr, this);
		}
	}
}

void APlayerCharacter::PlayFiringMontage_Implementation()
{
}

void APlayerCharacter::StartAiming_Implementation()
{
}

void APlayerCharacter::StopAiming_Implementation()
{
}



