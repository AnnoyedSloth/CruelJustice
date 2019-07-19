// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Pawn/CJBaseCharacter.h"
#include "CJPlayer.generated.h"

/**
 * 
 */

class ACJPlayerController;
class UCJPlayerAnimInstance;

UCLASS()
class CRUELJUSTICE_API ACJPlayer : public ACJBaseCharacter
{
	GENERATED_BODY()
	
	// For Properties
private:
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		UCameraComponent* camera;

	UPROPERTY()
		ACJPlayerController* playerController;

	UPROPERTY()
		UCJPlayerAnimInstance* animInstance;

	bool isKeyPressing;

	bool isAttacking;

	int32 currentCombo;

	// For Methods
private:


	// For Properties
protected:


	// For Methods
protected:

	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void Turn(float value);
	void LookUp(float value);
	
	void Attack();
	void AttackEnd();

	// For Properties
public:


	// For Methods
public:
	ACJPlayer();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float deltaTime) override;
	virtual void PossessedBy(AController* newController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent);

	void OnAttackMontageEnded(UAnimMontage* montage, bool isInterrupted);
	void AttackStartComboState();

	bool GetIsAttacking() const { return isAttacking; }
	
	
	
};
