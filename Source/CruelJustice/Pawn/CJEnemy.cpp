// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Controller/CJEnemyAIController.h"
#include "CJEnemyState.h"

ACJEnemy::ACJEnemy()
{
	enemyState = Cast<UCJEnemyState>(PlayerState);

}


