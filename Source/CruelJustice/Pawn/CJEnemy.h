// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Pawn/CJBaseCharacter.h"
#include "CJEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemy : public ACJBaseCharacter
{
	GENERATED_BODY()
	
public:

	// Set up as pure virtual function to prevent instanciation
	//virtual void Attack() = 0;
	
};
