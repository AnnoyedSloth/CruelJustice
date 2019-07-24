// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Pawn/CJPlayer.h"
#include "Controller/CJEnemyAIController.h"
#include "Animation/CJMonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "UI/CJEnemyWidget.h"
#include "CJGameInstance.h"

ACJEnemy::ACJEnemy()
{
	capsule->SetCollisionProfileName(TEXT("Enemy"));

	hpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		UI_HPBAR(TEXT("/Game/UI/UI_HPBar.UI_HPBar_C"));
	{
		hpWidget->SetWidgetClass(UI_HPBAR.Class);
		hpWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	hpWidget->SetupAttachment(mesh);
	hpWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	hpWidget->SetWidgetSpace(EWidgetSpace::Screen);

	
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

	UCJEnemyWidget* widget = Cast<UCJEnemyWidget>(hpWidget->GetUserWidgetObject());
	CJCHECK(widget);
	widget->BindCharacterStat(this);

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

	maxHP = enemyStat->hp;
	hp = maxHP;
	maxMP = enemyStat->mp;
	mp = maxMP;
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
		onHPChanged.Broadcast();
		if (hp < KINDA_SMALL_NUMBER)
		{
			onHPIsZero.Broadcast();
			player->AddExp(dropExp);
		}
	}

	return finalDamage;
}

float ACJEnemy::GetHPRatio()
{
	return hp < KINDA_SMALL_NUMBER ? 0.0f : (hp / maxHP);
}