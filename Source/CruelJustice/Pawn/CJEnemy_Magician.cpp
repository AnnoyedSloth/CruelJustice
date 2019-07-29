// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Magician.h"
#include "Animation/CJEnemy_Magician_AnimInstance.h"
#include "Controller/CJEnemy_Magician_Controller.h"
#include "Skill/CJProjectile_Fireball.h"

ACJEnemy_Magician::ACJEnemy_Magician()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonFey/Characters/Heroes/Fey/Meshes/Fey_GDC.Fey_GDC"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		BP_ANIM(TEXT("/Game/Animation/4_Magician/BP_Magician_Anim.BP_Magician_Anim_C"));
	if (BP_ANIM.Succeeded())
	{
		mesh->SetAnimInstanceClass(BP_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_DEAD(TEXT("/Game/Animation/4_Magician/AM_Magician_Dead.AM_Magician_Dead"));
	if (AM_DEAD.Succeeded())
	{
		deadAnim = AM_DEAD.Object;
	}

	AIControllerClass = ACJEnemy_Magician_Controller::StaticClass();
}

void ACJEnemy_Magician::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UCJEnemy_Magician_AnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
	}

	//// Repeating attack code for testing
	//FTimerHandle timerHandle;
	//GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ACJEnemy_Magician::Attack, 3.0f, true);

}

void ACJEnemy_Magician::AttackMontagePlay()
{
	Super::AttackMontagePlay();
}

void ACJEnemy_Magician::Attack()
{
	Super::Attack();

	ACJProjectile_Fireball* fireball = GetWorld()->SpawnActor<ACJProjectile_Fireball>(GetActorLocation(), GetActorRotation());
	fireball->SetProjectileOwner(this);
}