// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Magician_AnimInstance.h"
#include "ConstructorHelpers.h"

UCJEnemy_Magician_AnimInstance::UCJEnemy_Magician_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_ATTACK(TEXT("/Game/Animation/4_Magician/AM_Magician_Attack.AM_Magician_Attack"));
	CJCHECK(AM_ATTACK.Succeeded());
	attackMontage = AM_ATTACK.Object;

}


