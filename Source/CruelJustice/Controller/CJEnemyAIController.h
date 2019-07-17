// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "AIController.h"
#include "CJEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemyAIController : public AAIController
{
	GENERATED_BODY()


protected:
	UPROPERTY()
		class UBehaviorTree* btAsset;
	UPROPERTY()
		class UBlackboardData* bbAsset;
	

public:

	ACJEnemyAIController();
	virtual void Possess(APawn* pawn) override;
	virtual void UnPossess() override;
	
	
	
};
