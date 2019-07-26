// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Magician_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"


ACJEnemy_Magician_Controller::ACJEnemy_Magician_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BT_AI(TEXT("/Game/AI/3_Magician_BT.3_Magician_BT"));
	CJCHECK(BT_AI.Succeeded());
	btAsset = BT_AI.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BB_AI(TEXT("/Game/AI/3_Magician_BB.3_Magician_BB"));
	CJCHECK(BB_AI.Succeeded());
	bbAsset = BB_AI.Object;

}




