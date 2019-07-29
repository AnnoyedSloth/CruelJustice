// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Axeman.h"
#include "Controller/CJEnemy_Axeman_Controller.h"
#include "Animation/CJEnemy_Axeman_AnimInstance.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

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

	AIControllerClass = ACJEnemy_Axeman_Controller::StaticClass();

	attackRange = 150.0f;
	attackRadius = 150.0f;
	
}

void ACJEnemy_Axeman::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UCJEnemy_Axeman_AnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
	}

	//// Repeating attack code for testing
	//FTimerHandle timerHandle;
	//GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ACJEnemy_Axeman::AttackMontagePlay, 3.0f, true);
	
	// 애니메이션의 특정 동작에서 AttackNotify 함수가 Animation Instance에서 불리어지는데,
	// 
	animInstance->isAttackHit.AddUObject(this, &ACJEnemy_Axeman::Attack);
}

void ACJEnemy_Axeman::AttackMontagePlay()
{
	Super::AttackMontagePlay();
}

void ACJEnemy_Axeman::Attack()
{
	Super::Attack();

	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);
	bool result = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(attackRadius),
		//FCollisionShape::MakeCapsule(FVector(attackRange, attackRadius/2, attackRadius/2)),
		params
	);

	FCollisionShape::MakeCapsule(FVector());
	FVector traceVec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + traceVec * 0.5f;
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
		result.Actor->TakeDamage(attack, damageEvent, enemyAIController, this);
	}
}