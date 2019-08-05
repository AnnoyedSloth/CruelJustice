// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Blueprint/UserWidget.h"
#include "CJSkillList.generated.h"

/**
 * 
 */

UCLASS()
class CRUELJUSTICE_API UCJSkillList : public UUserWidget
{
	GENERATED_BODY()
	
private:
	TArray<class UButton*> skills;


public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(
		const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	void SetController(ACJPlayerController* ownerController);
};
