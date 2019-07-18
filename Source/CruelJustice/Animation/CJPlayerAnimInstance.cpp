// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerAnimInstance.h"

UCJPlayerAnimInstance::UCJPlayerAnimInstance()
{
	isInAir = false;
	isDead = false;
}

void UCJPlayerAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	auto pawn = TryGetPawnOwner();

	if (!IsValid(pawn)) return;
	
	if (!isDead)
	{
		curPawnSpeed = pawn->GetVelocity().Size();

		auto character = Cast<ACharacter>(pawn);
		if (character)
		{
			isInAir = character->GetMovementComponent()->IsFalling();
		}
	}

}


