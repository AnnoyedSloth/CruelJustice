// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CJEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UCJEnemyAnimInstance();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = true))
		UAnimMontage* deadAnim;

	void SetDeadAnim() { isDead = true; }
	
};
