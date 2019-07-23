// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Pawn/CJPlayer.h"
#include "Controller/CJEnemyAIController.h"
#include "Animation/CJMonsterAnimInstance.h"
#include "CJGameInstance.h"

ACJEnemy::ACJEnemy()
{
	capsule->SetCollisionProfileName(TEXT("Enemy"));
}

void ACJEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UCJMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
	}

	onHPIsZero.AddLambda([this]()->void {

		if (deadAnim) 
		{
			PlayAnimMontage(deadAnim);

			// Dead Animation montage가 끝난 이후 소멸되도록 설정
			SetLifeSpan(deadAnim->GetPlayLength() - 0.3f);
		}
		else
		{
			CJLOG(Warning, TEXT("Dead Anim is not valid"));
		}
	});
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
	float finalDamage = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	ACJPlayer* player = Cast<ACJPlayer>(damageCauser);

	if (player)
	{
		hp -= damageAmount;
		if (hp < KINDA_SMALL_NUMBER)
		{
			onHPIsZero.Broadcast();
			player->AddExp(dropExp);
		}
	}

	return finalDamage;
}