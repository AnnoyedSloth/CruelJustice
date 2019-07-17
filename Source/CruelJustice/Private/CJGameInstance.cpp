// Fill out your copyright notice in the Description page of Project Settings.

#include "CJGameInstance.h"
#include "ConstructorHelpers.h"

UCJGameInstance::UCJGameInstance()
{
	FString enemyStatPath = TEXT("/Game/DataSheet/MonsterStat.MonsterStat");
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_ENEMY_STAT(*enemyStatPath);

	if (DT_ENEMY_STAT.Succeeded())
	{
		enemyStat = DT_ENEMY_STAT.Object;
	}
	else
	{
		CJLOG_S(Warning);
	}

	FString enemyTransformPath = TEXT("/Game/DataSheet/MonsterTransformTable.MonsterTransformTable");
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_ENEMY_TRANSFORM(*enemyTransformPath);

	if (DT_ENEMY_TRANSFORM.Succeeded())
	{
		enemyTransform = DT_ENEMY_TRANSFORM.Object;
	}
	else
	{
		CJLOG_S(Warning);
	}
}

void UCJGameInstance::Init()
{
	Super::Init();

	for (auto elem : enemyTransform->RowMap)
	{
		//enemyTransform->FindRow<FCJEnemyTransform>(*FString::FromInt(elem.value), TEXT(""));
	}

}