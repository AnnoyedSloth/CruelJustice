// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CJProjectile.h"
#include "CJProjectile_Fireball.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJProjectile_Fireball : public ACJProjectile
{
	GENERATED_BODY()

private:
	UParticleSystemComponent* explosionParticle;

	float attackRange;

	float attackRadius;
	
protected:
	
	virtual void BeginPlay() override;

public:
	ACJProjectile_Fireball();

	virtual void SetProjectileOwner(ACJBaseCharacter* baseCharacter);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult) override;
	
};
