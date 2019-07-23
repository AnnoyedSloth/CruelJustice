// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/AnimInstance.h"
#include "CJPlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float curPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float accel;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		UAnimMontage* attackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
		UAnimMontage* rollMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		bool isAttacking;

private:

	UFUNCTION()
		void AnimNotify_AttackHitCheck();

	UFUNCTION()
		void AnimNotify_NextAttackCheck();


protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UCJPlayerAnimInstance();

	UFUNCTION()
		void PlayAttackMontage();

	UFUNCTION()
		void PlayRollMontage();

	UFUNCTION()
		void JumpToAttackMontageSection(int32 newSection);

	UFUNCTION()
		void JumpToRecoveryMontageSection(int32 newSection);
		
	UFUNCTION()
		FName GetAttackMontageSectionName(int32 section);

	UFUNCTION()
		FName GetRecoveryMontageSectionName(int32 section);

	FOnNextAttackCheckDelegate onNextAttackCheck;
	FOnAttackHitCheckDelegate onAttackHitCheck;
	
};
