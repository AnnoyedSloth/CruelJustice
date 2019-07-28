// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Axeman_AnimInstance.h"
#include "ConstructorHelpers.h"

UCJEnemy_Axeman_AnimInstance::UCJEnemy_Axeman_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_ATTACK(TEXT("/Game/Animation/2_Axeman/AM_Axeman_Attack.AM_Axeman_Attack"));
	CJCHECK(AM_ATTACK.Succeeded());
	attackMontage = AM_ATTACK.Object;
}


