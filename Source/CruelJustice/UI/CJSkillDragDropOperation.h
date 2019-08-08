// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Skill/CJSkill.h"
#include "CJSkillDragDropOperation.generated.h"

/**
 * 
 */
class UCJSkillWidget;

UCLASS()
class CRUELJUSTICE_API UCJSkillDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	ACJSkill* skill;
	TSubclassOf<class ACJSkill> skillPtr;
	FText name;
	
	
};
