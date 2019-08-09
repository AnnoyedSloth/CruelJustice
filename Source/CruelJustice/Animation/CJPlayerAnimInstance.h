// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/AnimInstance.h"
#include "CJPlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSkillDelegate1);
DECLARE_MULTICAST_DELEGATE(FOnSkillDelegate2);
DECLARE_MULTICAST_DELEGATE(FOnSkillDelegate3);

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	// ���� Animation�� �Ǵ��� �ٰŰ� �� ���µ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float curPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float accel;


	// ���� ���ݿ���� ���������� Ȯ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		bool isAttacking;

	// ���� ����� ��Ÿ��(Attack 4��, Recovery 3�� �� 7�� Section)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
		UAnimMontage* attackMontage;

	// ȸ�Ǳ� �ִϸ��̼� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
		UAnimMontage* rollMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		UAnimMontage* lvUpMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*> skillMontages;
private:
	
	// �ִϸ��̼� ��Ÿ�ֿ� ��ϵ� ��Ƽ����
	UFUNCTION()
		void AnimNotify_AttackHitCheck();

	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	UFUNCTION()
		void AnimNotify_Skill1();

	UFUNCTION()
		void AnimNotify_Skill2();

protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ledge, meta = (AllowPrivateAccess = true))
		bool canGrab;

public:
	UCJPlayerAnimInstance();

	UFUNCTION()
		void PlayAttackMontage();

	UFUNCTION()
		void PlayRollMontage();

	UFUNCTION()
		void PlayLvUpMontage();

	UFUNCTION()
		void PlayMontage(UAnimMontage* montage, float playRate);

	UFUNCTION()
		void JumpToAttackMontageSection(int32 newSection);

	UFUNCTION()
		void JumpToRecoveryMontageSection(int32 newSection);
		
	UFUNCTION()
		FName GetAttackMontageSectionName(int32 section);

	UFUNCTION()
		FName GetRecoveryMontageSectionName(int32 section);

	void AddSkillMontage(UAnimMontage* newMontage);

	FOnNextAttackCheckDelegate onNextAttackCheck;
	FOnAttackHitCheckDelegate onAttackHitCheck;
	FOnSkillDelegate1 skillDelegate1;
	FOnSkillDelegate2 skillDelegate2;
	FOnSkillDelegate3 skillDelegate3;

	UFUNCTION()
		void GrabWall(bool isGrab) { canGrab = isGrab; }
	
};
