// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/CJEnemy.h"
#include "CJEnemy_Magician.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemy_Magician : public ACJEnemy
{
	GENERATED_BODY()

private:
	class UCJMonsterAnimInstance* animInstance;
	
public:
	ACJEnemy_Magician();
	
	virtual void PostInitializeComponents() override;
	
};
