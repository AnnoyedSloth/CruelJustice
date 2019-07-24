// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerSkill1_Slash.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "Pawn/CJPlayer.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

ACJPlayerSkill1_Slash::ACJPlayerSkill1_Slash()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_SKILL1(TEXT("/Game/Animation/1_Player/Skills/AM_Player_Skill1_Slash.AM_Player_Skill1_Slash"));
	CJCHECK(AM_SKILL1.Succeeded());
	skillMontage = AM_SKILL1.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_SKILL(TEXT("/Game/ParagonKwang/FX/Particles/Abilities/LightStrike/FX/P_Kwang_LightStrike_Burst.P_Kwang_LightStrike_Burst"));
	CJCHECK(PS_SKILL.Succeeded());
	if (PS_SKILL.Succeeded())
	{
		CJLOG(Warning, TEXT("Particle import succeeded"));
	}
	else
	{
		CJLOG(Warning, TEXT("Particle import failed"));
	}
	//skillParticle->SetTemplate(PS_SKILL.Object);
	//skillParticle->bAutoActivate = false;

	attackRange = 200.0f;
	attackRadius = 200.0f;
}

//void ACJPlayerSkill1_Slash::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//
//	
//}

void ACJPlayerSkill1_Slash::PlaySkill()
{
	CJLOG(Warning, TEXT("Skill1 Play Start"));
	CJCHECK(animInstance);
	animInstance->skillDelegate1.AddLambda([this]()-> void {
		ApplyImpact();
	});
	animInstance->PlayMontage(skillMontage, 1.0f);
}

void ACJPlayerSkill1_Slash::ApplyImpact()
{

	//skillParticle->Activate(true);

	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);
	bool result = GetWorld()->SweepMultiByChannel(
		hitResults,
		owner->GetActorLocation(),
		owner->GetActorLocation() + owner->GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(attackRadius),
		//FCollisionShape::MakeCapsule(FVector(attackRange, attackRadius/2, attackRadius/2)),
		params
	);

	FCollisionShape::MakeCapsule(FVector());
	FVector traceVec = owner->GetActorForwardVector() * attackRange;
	FVector center = owner->GetActorLocation() + traceVec * 0.5f;
	float halfHeight = attackRange * 0.5f + attackRadius;
	FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
	FColor drawColor = result ? FColor::Green : FColor::Red;
	float debugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		center,
		halfHeight,
		attackRadius,
		capsuleRot,
		drawColor,
		false,
		debugLifeTime
	);

	for (FHitResult result : hitResults)
	{
		FDamageEvent damageEvent;
		result.Actor->TakeDamage(owner->GetAttack(), damageEvent, owner->GetController(), owner);
	}

	CJLOG(Warning, TEXT("AttackRate : %f"), owner->GetAttack());
	animInstance->skillDelegate1.Clear();
}
