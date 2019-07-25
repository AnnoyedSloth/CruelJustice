// Fill out your copyright notice in the Description page of Project Settings.

#include "CJProjectile.h"


// Sets default values
ACJProjectile::ACJProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	projectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));


	RootComponent = projectileCollision;
	particle->SetupAttachment(projectileCollision);
	   
	owner = nullptr;
}

// Called when the game starts or when spawned
void ACJProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACJProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACJProjectile::SetOwner(ACJBaseCharacter* newOwner)
{
	owner = newOwner;
}

void ACJProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult &SweepResult)
{

}