// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerState.h"
#include "CJGameInstance.h"

ACJPlayerState::ACJPlayerState()
{
	
}

void ACJPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UCJGameInstance* gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	FCJPlayerStat* statTable = gameInstance->GetPlayerStatData(1);

	maxHP = hp = statTable->maxHP;
	maxMP = mp = statTable->maxMP;
}

void ACJPlayerState::UpdatePlayerStat(int32 level)
{
	UCJGameInstance* gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	FCJPlayerStat* statTable = gameInstance->GetPlayerStatData(level);

	maxHP = statTable->maxHP;
	maxMP = statTable->maxMP;
}

void ACJPlayerState::ApplyDamage(float deltaHP)
{
	hp -= deltaHP;
}