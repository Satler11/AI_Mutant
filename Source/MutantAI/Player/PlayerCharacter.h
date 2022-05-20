// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MUTANTAI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool GetCanFire() const {
		return bCanFire;
	}

	UFUNCTION(BlueprintCallable)
	void SetCanFire(bool bCanFire_In) {
		bCanFire = bCanFire_In;
	}

	UFUNCTION(BlueprintCallable)
	bool GetIsAiming() const {
		return bIsAiming;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void PlayFiringMontage();

	UFUNCTION(BlueprintNativeEvent)
	void StartAiming();

	UFUNCTION(BlueprintNativeEvent)
	void StopAiming();

private:
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* GunAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ShootingDistance = 1500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ShootingCooldown = 0.2;

	UPROPERTY()
	bool bCanFire = true;

	bool bIsFiring = false;

	bool bIsAiming = false;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Turn(float AxisValue);

	void LookUp(float AxisValue);

	void ToggleFiring();

	void ToggleAiming();
	
	void Shoot();
};
