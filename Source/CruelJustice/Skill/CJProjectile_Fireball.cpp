// Fill out your copyright notice in the Description page of Project Settings.

#include "CJProjectile_Fireball.h"

ACJProjectile_Fireball::ACJProjectile_Fireball()
{

	projectileCollision->InitSphereRadius(5.0f);
	projectileCollision->BodyInstance.SetCollisionProfileName("Projectile");
	projectileCollision->Activate(true);

	movementComponent->InitialSpeed = 300.0f;
	
}

void ACJProjectile_Fireball::SetOwner(ACJBaseCharacter* newOwner)
{
	Super::SetOwner(newOwner);

	projectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ACJProjectile_Fireball::OnOverlapBegin);
}

void ACJProjectile_Fireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{

}


