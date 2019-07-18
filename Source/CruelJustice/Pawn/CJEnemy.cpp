// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Controller/CJEnemyAIController.h"
#include "CJEnemyState.h"

ACJEnemy::ACJEnemy()
{

}

void ACJEnemy::BeginPlay()
{
	Super::BeginPlay();

	ACJEnemyState* newEnemyState = Cast<ACJEnemyState>(PlayerState);
	if (!newEnemyState)
	{
		CJLOG(Warning, TEXT("enemyState does not exist"));
	}
	else
	{
		CJLOG(Warning, TEXT("enemyState does exist"));
	}
}

void ACJEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACJEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}