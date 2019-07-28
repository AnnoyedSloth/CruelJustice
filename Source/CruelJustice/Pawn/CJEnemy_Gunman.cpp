// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Gunman.h"
#include "Animation/CJEnemy_Gunman_AnimInstance.h"
#include "Controller/CJEnemy_Gunman_Controller.h"

ACJEnemy_Gunman::ACJEnemy_Gunman()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		BP_ANIM(TEXT("/Game/Animation/3_Gunman/BP_Gunman_Anim.BP_Gunman_Anim_C"));
	if (BP_ANIM.Succeeded())
	{
		mesh->SetAnimInstanceClass(BP_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_DEAD(TEXT("/Game/Animation/3_Gunman/AM_Gunman_Dead.AM_Gunman_Dead"));
	if (AM_DEAD.Succeeded())
	{
		deadAnim = AM_DEAD.Object;
	}

	AIControllerClass = ACJEnemy_Gunman_Controller::StaticClass();
}

void ACJEnemy_Gunman::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UCJEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
	}

}

void ACJEnemy_Gunman::Attack()
{
	Super::Attack();
}