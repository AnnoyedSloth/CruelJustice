// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CJBT_Decorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class CRUELJUSTICE_API UCJBT_Decorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(config, Category = Node, EditAnywhere)
		float attackRange;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp,
		uint8* nodeMemory) const override;
	
public:
	UCJBT_Decorator_IsInAttackRange();
	
};
