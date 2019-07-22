// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Magician.h"
#include "Animation/CJMonsterAnimInstance.h"

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

}

void ACJEnemy_Magician::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UCJMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
	}

	onHPIsZero.AddLambda([this]()->void {
		animInstance->SetDeadAnim();
		CJLOG(Warning, TEXT("Dead"));
	});

}
