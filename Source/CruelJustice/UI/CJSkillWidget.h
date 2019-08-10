// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CJSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJSkillWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UCJSkillList;
	
public:
	//class UButton* skillButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
	class UTextBlock* skillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
	TSubclassOf<class ACJSkill> skillPtr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = true))
		class ACJSkill* skill;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	void SetupSkillInfo(ACJSkill* otherSkill);
	void Play();

};
