// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ACJEnemyAIController::ACJEnemyAIController()
{

}

void ACJEnemyAIController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

}

void ACJEnemyAIController::UnPossess()
{
	Super::UnPossess();

}