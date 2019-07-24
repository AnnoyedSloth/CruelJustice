// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CJSkill.h"
#include "CJPlayerSkill1_Slash.generated.h"

/**
 * 
 */

class ACJPlayer;

UCLASS()
class CRUELJUSTICE_API ACJPlayerSkill1_Slash : public ACJSkill
{
	GENERATED_BODY()
		
private:
	float attackRange;
	float attackRadius;
	
public:
	ACJPlayerSkill1_Slash();

	//virtual void PostInitializeComponents() override;

	virtual void PlaySkill() override;
	virtual void ApplyImpact() override;
};
