// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Gunman_AnimInstance.h"
#include "ConstructorHelpers.h"

UCJEnemy_Gunman_AnimInstance::UCJEnemy_Gunman_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_ATTACK(TEXT("/Game/Animation/3_Gunman/AM_Gunman_Attack.AM_Gunman_Attack"));
	CJCHECK(AM_ATTACK.Succeeded());
	attackMontage = AM_ATTACK.Object;
}
