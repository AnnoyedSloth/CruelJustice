// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerAnimInstance.h"
#include "Pawn/CJPlayer.h"
#include "ConstructorHelpers.h"

UCJPlayerAnimInstance::UCJPlayerAnimInstance()
{
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_ATTACK(TEXT("/Game/Animation/1_Player/AM_Player_Attack.AM_Player_Attack"));
	CJCHECK(AM_ATTACK.Succeeded());
	attackMontage = AM_ATTACK.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_ROLL(TEXT("/Game/Animation/1_Player/AM_Player_RollForward.AM_Player_RollForward"));
	CJCHECK(AM_ROLL.Succeeded());
	rollMontage = AM_ROLL.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_LVUP(TEXT("/Game/Animation/1_Player/AM_Player_LvUp.AM_Player_LvUp"));
	CJCHECK(AM_LVUP.Succeeded());
	lvUpMontage = AM_LVUP.Object;

	isInAir = false;
	isDead = false;
}

void UCJPlayerAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	auto pawn = TryGetPawnOwner();

	if (!IsValid(pawn)) return;
	
	if (!isDead)
	{
		curPawnSpeed = pawn->GetVelocity().Size();

		auto character = Cast<ACJPlayer>(pawn);
		if (character)
		{
			isInAir = character->GetMovementComponent()->IsFalling();
			accel = character->GetCharacterMovement()->GetCurrentAcceleration().Size();
			isAttacking = character->GetIsAttacking();
		}
	}
}

void UCJPlayerAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(attackMontage))
	{
		Montage_Play(attackMontage, 1.0f);
	}
}

void UCJPlayerAnimInstance::PlayRollMontage()
{
	if (!Montage_IsPlaying(rollMontage))
	{
		Montage_Play(rollMontage, 1.0f);
	}
}

void UCJPlayerAnimInstance::PlayLvUpMontage()
{
	if (lvUpMontage)
	{
		Montage_Play(lvUpMontage, 1.0f);
	}
}

void UCJPlayerAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(newSection), attackMontage);
}

void UCJPlayerAnimInstance::JumpToRecoveryMontageSection(int32 newSection)
{
	Montage_JumpToSection(GetRecoveryMontageSectionName(newSection), attackMontage);
}

FName UCJPlayerAnimInstance::GetAttackMontageSectionName(int32 section)
{
	CJCHECK(FMath::IsWithinInclusive<int32>(section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), section));
}

FName UCJPlayerAnimInstance::GetRecoveryMontageSectionName(int32 section)
{
	int32 newSection = FMath::Clamp(section, 1, 3);
	return FName(*FString::Printf(TEXT("Recovery%d"), newSection));
}

void UCJPlayerAnimInstance::AnimNotify_AttackHitCheck()
{
	onAttackHitCheck.Broadcast();
}

void UCJPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	onNextAttackCheck.Broadcast();
}