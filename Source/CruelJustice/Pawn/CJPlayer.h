// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Pawn/CJBaseCharacter.h"
#include "CJPlayer.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

class ACJPlayerController;
class UCJPlayerAnimInstance;
class ACJPlayerState;

UCLASS()
class CRUELJUSTICE_API ACJPlayer : public ACJBaseCharacter
{
	GENERATED_BODY()
	
	// For Properties
private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		UCameraComponent* camera;

	UPROPERTY()
		ACJPlayerController* playerController;

	UPROPERTY()
		UCJPlayerAnimInstance* animInstance;

	// Attack Combo related
	bool isAttacking;

	int32 currentCombo;

	int32 recoveryCombo;

	FOnAttackEndDelegate onAttackEnd;

	// Status Values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 curExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 nextExp;

	ACJPlayerState* playerState;

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

	void AttackCheck();

	UFUNCTION()
		void AddExp(int32 incomeExp);

	UFUNCTION()
		void LevelUp();

	UFUNCTION()
		virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent,
			class AController* eventInstigator, AActor* damageCauser) override;
	
	
	
};
