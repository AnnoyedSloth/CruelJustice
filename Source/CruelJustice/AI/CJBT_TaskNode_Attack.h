// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CJBT_TaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJBT_TaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCJBT_TaskNode_Attack();
	
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	
};
