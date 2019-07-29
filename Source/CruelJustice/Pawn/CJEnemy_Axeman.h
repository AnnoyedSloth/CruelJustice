// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/CJEnemy.h"
#include "CJEnemy_Axeman.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemy_Axeman : public ACJEnemy
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = Stat)
		float attackRange;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float attackRadius;

public:
	ACJEnemy_Axeman();
	virtual void PostInitializeComponents() override;
	virtual void AttackMontagePlay() override;
	virtual void Attack() override;

};
