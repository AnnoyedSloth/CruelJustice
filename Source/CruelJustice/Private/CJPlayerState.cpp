// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerState.h"
#include "CJGameInstance.h"

ACJPlayerState::ACJPlayerState()
{
	level = 1;
	
}

void ACJPlayerState::SetHP(float deltaHP)
{
	hp += deltaHP;
}

void ACJPlayerState::SetMP(float deltaMP)
{
	mp += deltaMP;
}

void ACJPlayerState::AddExp(int32 incomeExp)
{
	curExp += incomeExp;

	if (curExp > nextExp)
	{
		LevelUp();
	}
}

void ACJPlayerState::LevelUp()
{
	auto gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	CJCHECK(gameInstance);

	level += 1;
	curExp = 0;

	maxHP = gameInstance->GetPlayerStatData(level)->maxHP;
	maxMP = gameInstance->GetPlayerStatData(level)->maxMP;
	nextExp = gameInstance->GetPlayerStatData(level)->nextExp;


}