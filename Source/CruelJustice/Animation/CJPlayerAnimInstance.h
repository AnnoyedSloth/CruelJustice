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

	// 현재 Animation을 판단할 근거가 될 상태들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float curPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float accel;

	// 현재 공격연계기 진행중인지 확인
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		bool isAttacking;

	// 공격 연계기 몽타주(Attack 4개, Recovery 3개 총 7개 Section)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		UAnimMontage* attackMontage;

	// 회피기 애니메이션 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
		UAnimMontage* rollMontage;

private:
	
	// 애니메이션 몽타주에 등록된 노티파이
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
