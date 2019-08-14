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
	TArray<class UCJSkillWidget*> skills;
	class UButton* closeButton;

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(
		const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void Close();

	UFUNCTION()
		void Skill1();

	UFUNCTION()
		void Skill2();
};