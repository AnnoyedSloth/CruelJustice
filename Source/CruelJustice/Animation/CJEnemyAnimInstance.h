// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/AnimInstance.h"
#include "CJEnemyAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

UCLASS()
class CRUELJUSTICE_API UCJEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		float speed;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Montage, meta = (AllowPrivateAccess=true))
	UAnimMontage* attackMontage;


protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	FOnAttackHit isAttackHit;

public:
	UCJEnemyAnimInstance();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = true))
		UAnimMontage* deadAnim;

	void SetDeadAnim() { isDead = true; }

	UFUNCTION()
	virtual void AnimNotify_AttackNotify();

	UFUNCTION()
		virtual void PlayAttackMontage();
	
};
