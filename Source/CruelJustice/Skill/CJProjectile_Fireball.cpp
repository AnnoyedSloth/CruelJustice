// Fill out your copyright notice in the Description page of Project Settings.

#include "CJProjectile_Fireball.h"
#include "Pawn/CJBaseCharacter.h"
#include "Pawn/CJPlayer.h"
#include "CJCameraShake.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

ACJProjectile_Fireball::ACJProjectile_Fireball()
{
	explosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	explosionParticle->SetupAttachment(RootComponent);
	explosionParticle->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_FIRE(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_FireBall_Base.P_FireBall_Base"));
	CJCHECK(PS_FIRE.Succeeded());
	particle->SetTemplate(PS_FIRE.Object);
	particle->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_EXPLOSION(TEXT("/Game/Explosions/Particles/P_ImpactExplosion2.P_ImpactExplosion2"));
	explosionParticle->SetTemplate(PS_EXPLOSION.Object);

	projectileCollision->InitSphereRadius(30.0f);
	projectileCollision->Activate(true);

	explosionParticle->bAutoActivate = false;

	movementComponent->InitialSpeed = 1000.0f;
	movementComponent->ProjectileGravityScale = 1.0f;

	attackRange = 400.0f;
	attackRadius = 400.0f;
}

void ACJProjectile_Fireball::BeginPlay()
{
	Super::BeginPlay();
	projectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ACJProjectile_Fireball::OnOverlapBegin);
}

void ACJProjectile_Fireball::SetProjectileOwner(ACJBaseCharacter* newOwner)
{
	Super::SetProjectileOwner(newOwner);

}

void ACJProjectile_Fireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//CJLOG(Warning, TEXT("OtherActorName = %s"),*OtherActor->GetName());

	if (!skillInstigator) return;

	TSubclassOf<UCJCameraShake> cameraShake = UCJCameraShake::StaticClass();
	if (cameraShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(cameraShake, 1.0f);
	}

	ACJBaseCharacter* otherCharacter = Cast<ACJBaseCharacter>(OtherActor);

	//CJLOG(Warning, TEXT("Other Actor"));
	movementComponent->StopSimulating(SweepResult);
	particle->Deactivate();

	explosionParticle->Activate(false);

	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);
	bool result = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() * attackRange,
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
		if (otherCharacter == skillInstigator) continue;
		FDamageEvent damageEvent;
		result.Actor->TakeDamage(skillInstigator->GetAttack(), damageEvent, skillInstigator->GetController(), skillInstigator);
	}

	SetLifeSpan(3.0f);
	


}