// Fill out your copyright notice in the Description page of Project Settings.

#include "CJBT_TaskNode_Attack.h"
#include "Pawn/CJEnemy.h"
#include "Controller/CJEnemyAIController.h"

UCJBT_TaskNode_Attack::UCJBT_TaskNode_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UCJBT_TaskNode_Attack::ExecuteTask(
	UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(ownerComp, nodeMemory);

	ACJEnemy* owner = Cast<ACJEnemy>(ownerComp.GetAIOwner()->GetPawn());

	if (!owner)
	{
		CJLOG(Warning, TEXT("Casting failed"));
		return EBTNodeResult::Failed;
	}

	owner->AttackMontagePlay();
	return EBTNodeResult::Succeeded;
}


