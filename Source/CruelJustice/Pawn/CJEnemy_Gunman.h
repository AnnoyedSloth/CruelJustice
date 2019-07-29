// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/CJEnemy.h"
#include "CJEnemy_Gunman.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemy_Gunman : public ACJEnemy
{
	GENERATED_BODY()

private:
	//class UCJEnemyAnimInstance* animInstance;

	//UAnimMontage* deadAnim;
public:
	
	ACJEnemy_Gunman();

	virtual void PostInitializeComponents() override;
	virtual void AttackMontagePlay() override;
	virtual void Attack() override;
	
};
