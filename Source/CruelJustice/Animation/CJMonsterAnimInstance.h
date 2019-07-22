// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CJMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
		bool isDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = true))
		UAnimMontage* deadAnim;

protected:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UCJMonsterAnimInstance();

	void SetDeadAnim() { isDead = true; }
	
};
