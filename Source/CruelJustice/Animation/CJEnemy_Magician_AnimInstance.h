// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/CJEnemyAnimInstance.h"
#include "CJEnemy_Magician_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJEnemy_Magician_AnimInstance : public UCJEnemyAnimInstance
{
	GENERATED_BODY()

private:
	UAnimMontage* attackMontage;
	
public:
	UCJEnemy_Magician_AnimInstance();
	
};
