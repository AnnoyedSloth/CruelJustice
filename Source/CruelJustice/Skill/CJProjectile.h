// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CJProjectile.generated.h"

class ACJBaseCharacter;

UCLASS()
class CRUELJUSTICE_API ACJProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACJProjectile();

protected:
	UPROPERTY()
	USphereComponent* projectileCollision;

	UPROPERTY()
	UProjectileMovementComponent* movementComponent;

	UPROPERTY()
	UParticleSystemComponent* particle;

	UPROPERTY(VisibleAnywhere, Category = Status)
	ACJBaseCharacter* skillInstigator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetProjectileOwner(ACJBaseCharacter* baseCharacter);

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UProjectileMovementComponent* GetMovementComponent() { return movementComponent; }

	
	
};
