// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/PlayerController.h"
#include "CJPlayerController.generated.h"

/**
 * 
 */

class ACJPlayerState;

UCLASS()
class CRUELJUSTICE_API ACJPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend class  UCJCustomKeyWidget;
	friend class UCJShortcut;
	friend class UCJSkillList;
	friend class UCJSkillWidget;

private:
	TSubclassOf<class UCJCustomKeyWidget> customKeyWidgetClass;
	class UCJCustomKeyWidget* customKeyWidget;

	TSubclassOf<class UCJShortcut> shortcutWidgetClass;
	class UCJShortcut* shortcutWidget;

	TSubclassOf<class UCJSkillList> skillListWidgetClass;
	class UCJSkillList* skillListWidget;

	TSubclassOf<class UCJSkillWidget> skillWidgetClass;
	class UCJSkillWidget* skillWidget;
	
protected:
	virtual void BeginPlay() override;
	
public:
	ACJPlayerState* playerState;

public:
	ACJPlayerController();
	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* pawn) override;
	virtual void UnPossess() override;
	void MouseCursorToggle();
	void TurnOnCustomWidget();
	void TurnOnSkillWidget();

	UCJShortcut* GetShortcutWidget() { return shortcutWidget; }
	
};
