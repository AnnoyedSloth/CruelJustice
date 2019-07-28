// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/CJEnemyAIController.h"
#include "CJEnemy_Axeman_Controller.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheck);

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemy_Axeman_Controller : public ACJEnemyAIController
{
	GENERATED_BODY()
	
public:
	ACJEnemy_Axeman_Controller();
	
	FOnAttackHitCheck attackHit;
	
};
