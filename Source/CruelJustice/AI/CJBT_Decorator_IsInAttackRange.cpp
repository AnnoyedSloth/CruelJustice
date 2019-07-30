// Fill out your copyright notice in the Description page of Project Settings.

#include "CJBT_Decorator_IsInAttackRange.h"
#include "Controller/CJEnemyAIController.h"
#include "Pawn/CJBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UCJBT_Decorator_IsInAttackRange::UCJBT_Decorator_IsInAttackRange()
{
	NodeName = TEXT("CJIsInAttackRange");
	attackRange = 200.0f;
}

bool UCJBT_Decorator_IsInAttackRange::CalculateRawConditionValue(
	UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(ownerComp, nodeMemory);

	APawn* controllingPawn = ownerComp.GetAIOwner()->GetPawn();
	if (!controllingPawn) return false;

	ACJBaseCharacter* target = Cast<ACJBaseCharacter>(
		ownerComp.GetBlackboardComponent()->GetValueAsObject(ACJEnemyAIController::targetKey));

	if (!target) return false;

	result = (target->GetDistanceTo(controllingPawn) <= attackRange);
	return result;

}


