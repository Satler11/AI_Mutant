// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MutantAIController.h"

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

	void ChangeSpeed(EState NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayTurnMontage(bool bIsTurningLeft);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopTurnMontage(bool bIsTurningLeft);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void OnAttackMontageEnd();

	bool GetIsPlayingAttackMontage() {
		return bIsPlayingAttackMontage;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	float WanderingSpeed = 150;
	
	UPROPERTY(EditDefaultsOnly)
	float HuntingSpeed = 300;

	UPROPERTY(EditDefaultsOnly)
	float AttackingSpeed = 400;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsPlayingAttackMontage = false;

	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

};
