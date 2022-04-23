// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MutantCharacter.generated.h"

UCLASS()
class MUTANTAI_API AMutantCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMutantCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayTurnMontage(bool bIsTurningLeft);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopTurnMontage(bool bIsTurningLeft);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
