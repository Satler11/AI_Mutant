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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComponent;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Turn(float AxisValue);

	void LookUp(float AxisValue);
};
