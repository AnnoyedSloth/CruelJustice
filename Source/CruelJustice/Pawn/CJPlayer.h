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
class ACJSkill;

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

	UPROPERTY()
		UParticleSystemComponent* lvUpParticle;

	// Attack related
	bool isAttacking;

	int32 currentCombo;

	int32 recoveryCombo;

	FOnAttackEndDelegate onAttackEnd;

	UPROPERTY(VisibleAnywhere, Category = Attack, meta = (AllowPrivateAccess = true))
		float attackRange;

	UPROPERTY(VisibleAnywhere, Category = Attack, meta = (AllowPrivateAccess = true))
		float attackRadius;

	// Status Values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 curExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 nextExp;

	ACJPlayerState* playerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
	TArray<ACJSkill*> skills;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
	ACJSkill* curSkill;

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

	void ToggleCursor();
	void TurnOnKeyUI();
	
	// For Properties
public:


	// For Methods
public:
	ACJPlayer();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float deltaTime) override;
	virtual void PossessedBy(AController* newController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent);

	UCJPlayerAnimInstance* GetAnimInstance() { return animInstance; }

	//ACJPlayerState* GetPlayerState() { return playerState; }

	float GetAttack() const { return attack; }

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool isInterrupted);
	void AttackStartComboState();

	void Attack();
	void AttackEnd();

	bool GetIsAttacking() const { return isAttacking; }

	void AttackCheck();

	//Skills
	UFUNCTION()
		void Dodge();

	void Skill1();

	void Skill2();

	// Levelup
	UFUNCTION()
		void AddExp(int32 incomeExp);

	UFUNCTION()
		void LevelUp();

	UFUNCTION()
		virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent,
			class AController* eventInstigator, AActor* damageCauser) override;
	
	
	
};
