// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Axeman.h"
#include "Animation/CJMonsterAnimInstance.h"
#include "ConstructorHelpers.h"

ACJEnemy_Axeman::ACJEnemy_Axeman()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		BP_ANIM(TEXT("/Game/Animation/2_Axeman/BP_Axeman_Anim.BP_Axeman_Anim_C"));
	if (BP_ANIM.Succeeded())
	{
		mesh->SetAnimInstanceClass(BP_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_DEAD(TEXT("/Game/Animation/2_Axeman/AM_Axeman_Dead.AM_Axeman_Dead"));
	if (AM_DEAD.Succeeded())
	{
		deadAnim = AM_DEAD.Object;
	}
	
}


void ACJEnemy_Axeman::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}