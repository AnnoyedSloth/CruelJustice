// Fill out your copyright notice in the Description page of Project Settings.

#include "CJProjectile.h"


// Sets default values
ACJProjectile::ACJProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));


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

