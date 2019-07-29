// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/CJEnemyAnimInstance.h"
#include "CJEnemy_Gunman_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJEnemy_Gunman_AnimInstance : public UCJEnemyAnimInstance
{
	GENERATED_BODY()
	
private:
	UAnimMontage* attackMontage;

public:
	UCJEnemy_Gunman_AnimInstance();
	
	
};
