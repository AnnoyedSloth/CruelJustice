// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemyAIController.h"
#include "Pawn/CJPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ACJEnemyAIController::ACJEnemyAIController()
{
	homePosKey = TEXT("HomePosition");
	patrolPosKey = TEXT("PatrolPosition");
	targetKey = TEXT("Target");
}

void ACJEnemyAIController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

}

void ACJEnemyAIController::UnPossess()
{
	Super::UnPossess();

}

void ACJEnemyAIController::StartAI()
{
	if (UseBlackboard(bbAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(btAsset))
		{
			CJLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void ACJEnemyAIController::StopAI()
{
	auto behaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (behaviorTreeComponent)
	{
		// 트리 정지
		behaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ACJEnemyAIController::SetPlayerCaught(APawn* pawn)
{
	ACJPlayer* player = Cast<ACJPlayer>(pawn);
	if (player)
	{
		Blackboard->SetValueAsObject(targetKey, player);
	}
}