// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy.h"
#include "Pawn/CJPlayer.h"
#include "Controller/CJEnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Animation/CJEnemyAnimInstance.h"
#include "UI/CJEnemyWidget.h"
#include "Perception/PawnSensingComponent.h"
#include "CJGameInstance.h"

ACJEnemy::ACJEnemy()
{
	capsule->SetCollisionProfileName(TEXT("Enemy"));

	hpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));

	pawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
	pawnSensingComp->SetPeripheralVisionAngle(50.0f);
	pawnSensingComp->HearingThreshold = 500.0f;
	pawnSensingComp->SightRadius = 2500.0f;
	pawnSensingComp->SensingInterval = 1.0f;

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

	enemyAIController = Cast<ACJEnemyAIController>(GetController());
	CJCHECK(enemyAIController);

	CJCHECK(pawnSensingComp);
	pawnSensingComp->OnSeePawn.AddDynamic(this, &ACJEnemy::PlayerCaught);
	//pawnSensingComp->OnHearNoise.AddDynamic(this, &ACJEnemy::PlayerCaught);

	UCJEnemyWidget* widget = Cast<UCJEnemyWidget>(hpWidget->GetUserWidgetObject());
	CJCHECK(widget);
	widget->BindCharacterStat(this);

	

}

void ACJEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (enemyAIController)
	{
		enemyAIController->StartAI();
	}

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
			SetActorEnableCollision(false);
			bCanBeDamaged = false;
			player->AddExp(dropExp);
		}
	}

	return finalDamage;
}

float ACJEnemy::GetHPRatio()
{
	return hp < KINDA_SMALL_NUMBER ? 0.0f : (hp / maxHP);
}

void ACJEnemy::AttackMontagePlay()
{
	if (!animInstance) return;
	animInstance->PlayAttackMontage();
}

void ACJEnemy::Attack()
{

}

void ACJEnemy::PlayerCaught(APawn* pawn)
{
	enemyAIController->SetPlayerCaught(pawn);
}