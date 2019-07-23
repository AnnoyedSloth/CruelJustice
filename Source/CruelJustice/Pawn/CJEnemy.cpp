// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Controller/CJEnemyAIController.h"
#include "CJGameInstance.h"

ACJEnemy::ACJEnemy()
{

}

void ACJEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACJEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ACJEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void ACJEnemy::InitStatData(int32 monsterID)
{
	UCJGameInstance* gameInstance = Cast<UCJGameInstance>(GetGameInstance());

	if (!gameInstance)
	{
		CJLOG(Warning, TEXT("Game instance missing"));
	}

	FCJEnemyStat* enemyStat = gameInstance->GetEnemyStatData(monsterID);

	hp = enemyStat->hp;
	mp = enemyStat->mp;
	attack = enemyStat->attack;
	defense = enemyStat->defense;
	dropExp = enemyStat->exp;

}

float ACJEnemy::TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent,
	class AController* eventInstigator, AActor* damageCauser)
{
	float finalDamage = TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	if (damageCauser->Tags[0] == FName("Player"))
	{
		hp -= damageAmount;
		if (hp < KINDA_SMALL_NUMBER)
		{
			onHPIsZero.Broadcast();
		}
	}

	return finalDamage;
}