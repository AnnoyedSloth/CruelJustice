// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerSkill2_Fireball.h"
#include "CJProjectile_Fireball.h"
#include "Pawn/CJPlayer.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "ConstructorHelpers.h"

ACJPlayerSkill2_Fireball::ACJPlayerSkill2_Fireball()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_SKILL2(TEXT("/Game/Animation/1_Player/Skills/AM_Player_Skill2_Fireball.AM_Player_Skill2_Fireball"));
	CJCHECK(AM_SKILL2.Succeeded());
	skillMontage = AM_SKILL2.Object;

	InitialLifeSpan = 3.0f;

}

void ACJPlayerSkill2_Fireball::PlaySkill()
{
	CJCHECK(animInstance);
	animInstance->skillDelegate2.AddLambda([this]()-> void {
		ApplyImpact();
	});
	animInstance->PlayMontage(skillMontage, 1.0f);
}

void ACJPlayerSkill2_Fireball::ApplyImpact()
{
	FRotator spawnRotation = skillInstigator->GetActorRotation();
	//spawnRotation.RotateVector(FVector(100.0f, 0.0f, 0.0f));
	spawnRotation.Pitch = 50.0f;

	//CJLOG(Warning, TEXT("Pitch : %f, Yaw : %f, Roll : %f"), spawnRotation.Pitch, spawnRotation.Yaw, spawnRotation.Roll);
	ACJProjectile_Fireball* newPjt = GetWorld()->SpawnActor<ACJProjectile_Fireball>(skillInstigator->GetActorLocation(), spawnRotation);
	newPjt->SetProjectileOwner(skillInstigator);

	animInstance->skillDelegate2.Clear();
}


