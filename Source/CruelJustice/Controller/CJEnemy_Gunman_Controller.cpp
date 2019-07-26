// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Gunman_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"

ACJEnemy_Gunman_Controller::ACJEnemy_Gunman_Controller()
{

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BT_AI(TEXT("/Game/AI/2_Gunman_BT.2_Gunman_BT"));
	CJCHECK(BT_AI.Succeeded());
	btAsset = BT_AI.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BB_AI(TEXT("/Game/AI/2_Gunman_BB.2_Gunman_BB"));
	CJCHECK(BB_AI.Succeeded());
	bbAsset = BB_AI.Object;

	
}


