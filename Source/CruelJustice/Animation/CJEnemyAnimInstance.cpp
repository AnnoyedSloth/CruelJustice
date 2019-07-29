// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemyAnimInstance.h"

UCJEnemyAnimInstance::UCJEnemyAnimInstance()
{
	isDead = false;

}

void UCJEnemyAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

}

void UCJEnemyAnimInstance::AnimNotify_AttackNotify()
{
	if (!attackMontage) return;
	isAttackHit.Broadcast();
}

void UCJEnemyAnimInstance::PlayAttackMontage()
{
	if (!attackMontage)
	{
		CJLOG(Warning, TEXT("Attack montage missing"));
	}
	Montage_Play(attackMontage);
}