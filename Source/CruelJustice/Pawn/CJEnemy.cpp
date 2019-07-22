// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Controller/CJEnemyAIController.h"
#include "CJGameInstance.h"

ACJEnemy::ACJEnemy()
{

}

void ACJEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ACJEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void ACJEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void ACJEnemy::InitStatData(int32 monsterID)
{
	UCJGameInstance* gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	FCJEnemyStat* enemyStat = gameInstance->GetEnemyStatData(monsterID);

	hp = enemyStat->hp;
	mp = enemyStat->mp;
	attack = enemyStat->attack;
	defense = enemyStat->defense;
	dropExp = enemyStat->exp;

}