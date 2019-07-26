// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Axeman_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"

ACJEnemy_Axeman_Controller::ACJEnemy_Axeman_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BT_AI(TEXT("/Game/AI/1_Axeman_BT.1_Axeman_BT"));
	CJCHECK(BT_AI.Succeeded());
	btAsset = BT_AI.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BB_AI(TEXT("/Game/AI/1_Axeman_BB.1_Axeman_BB"));
	CJCHECK(BB_AI.Succeeded());
	bbAsset = BB_AI.Object;
}


