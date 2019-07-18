// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Animation/AnimInstance.h"
#include "CJPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float curPawnSpeed;

protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UCJPlayerAnimInstance();
	
};
