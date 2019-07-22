// Fill out your copyright notice in the Description page of Project Settings.

#include "CJGameInstance.h"
#include "ConstructorHelpers.h"
#include "Pawn/CJEnemy_Axeman.h"
#include "Pawn/CJEnemy_Gunman.h"
#include "Pawn/CJEnemy_Magician.h"

UCJGameInstance::UCJGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_ENEMY_STAT(TEXT("/Game/DataSheet/MonsterStat.MonsterStat"));

	if (DT_ENEMY_STAT.Succeeded())
	{
		enemyStatTable = DT_ENEMY_STAT.Object;
	}
	else
	{
		CJLOG(Warning, TEXT("Failed to find EnemyStat"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_ENEMY_TRANSFORM(TEXT("/Game/DataSheet/MonsterTransformTable.MonsterTransformTable"));
	if (DT_ENEMY_TRANSFORM.Succeeded())
	{
		enemyTransformTable = DT_ENEMY_TRANSFORM.Object;
	}
	else
	{
		CJLOG(Warning, TEXT("Failed to find EnemyTransform"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_PLAYER_STAT(TEXT("/Game/DataSheet/PlayerStat.PlayerStat"));
	if (DT_PLAYER_STAT.Succeeded())
	{
		playerStatTable = DT_PLAYER_STAT.Object;
	}
	else
	{
		CJLOG(Warning, TEXT("Failed to find PlayerStat"));
	}
}

void UCJGameInstance::Init()
{
	Super::Init();

	TArray<FCJEnemyTransform*> tableArr;	
	enemyTransformTable->GetAllRows(TEXT(""), tableArr);

	CJLOG(Warning, TEXT("Num of table : %d"), tableArr.Num());
	
	for (int a = 0; a < tableArr.Num(); ++a)
	{
		FVector actorLocation(tableArr[a]->x, tableArr[a]->y, tableArr[a]->z + 110.0f);
		FRotator actorRotation(0, tableArr[a]->yaw, 0);

		int32 actorID = tableArr[a]->monsterID;

		UWorld* world = GetWorld();

		// Factory function
		switch (actorID)
		{
		case 1:
		{
			ACJEnemy_Axeman* axeman = world->SpawnActor<ACJEnemy_Axeman>(actorLocation, actorRotation);
			axeman->InitStatData(actorID);
		}
			break;

		case 2:
		{
			ACJEnemy_Gunman* gunman = world->SpawnActor<ACJEnemy_Gunman>(actorLocation, actorRotation);
			gunman->InitStatData(actorID);
		}
		break;

		case 3:
		{
			ACJEnemy_Magician* magician = world->SpawnActor<ACJEnemy_Magician>(actorLocation, actorRotation);
			magician->InitStatData(actorID);
		}
		break;
		default:
			break;
		}

	}
}

FCJEnemyStat* UCJGameInstance::GetEnemyStatData(int32 id)
{
	if (enemyStatTable) return enemyStatTable->FindRow<FCJEnemyStat>(*FString::FromInt(id), TEXT(""));
	return nullptr;
}

FCJEnemyTransform* UCJGameInstance::GetEnemyTransformData(int32 id)
{
	if (enemyTransformTable) return enemyTransformTable->FindRow<FCJEnemyTransform>(*FString::FromInt(id), TEXT(""));
	return nullptr;
}

FCJPlayerStat* UCJGameInstance::GetPlayerStatData(int32 level)
{
	if (playerStatTable) return playerStatTable->FindRow<FCJPlayerStat>(*FString::FromInt(level), TEXT(""));
	return nullptr;
}