// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Skill/CJSkill.h"
#include "CJPlayerSkill2_Fireball.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJPlayerSkill2_Fireball : public ACJSkill
{
	GENERATED_BODY()

private:
	
public:
	ACJPlayerSkill2_Fireball();

	virtual void PlaySkill() override;
	virtual void ApplyImpact() override;

	
};
