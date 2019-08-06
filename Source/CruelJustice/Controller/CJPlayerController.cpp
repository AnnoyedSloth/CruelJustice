// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerController.h"
#include "Pawn/CJPlayer.h"
#include "UI/CJCustomKeyWidget.h"
#include "UI/CJShortcut.h"
#include "UI/CJSkillList.h"
#include "UI/CJSkillWidget.h"
#include "CJPlayerState.h"
#include "ConstructorHelpers.h"

ACJPlayerController::ACJPlayerController()
{	
	static ConstructorHelpers::FClassFinder<UCJCustomKeyWidget>
		UI_CUSTOM(TEXT("/Game/UI/CustomKey.CustomKey_C"));
	if (UI_CUSTOM.Succeeded())
	{
		customKeyWidgetClass = UI_CUSTOM.Class;
	}

	static ConstructorHelpers::FClassFinder<UCJShortcut>
		UI_SHORTCUT(TEXT("/Game/UI/Shortcut.Shortcut_C"));
	if (UI_SHORTCUT.Succeeded())
	{
		shortcutWidgetClass = UI_SHORTCUT.Class;
	}

	static ConstructorHelpers::FClassFinder<UCJSkillList>
		UI_SKILLLIST(TEXT("/Game/UI/SkillList.SkillList_C"));
	if (UI_SKILLLIST.Succeeded())
	{
		skillListWidgetClass = UI_SKILLLIST.Class;
	}

	static ConstructorHelpers::FClassFinder<UCJSkillWidget>
		WIDGET_SKILL(TEXT("/Game/UI/Skill.Skill_C"));
	if (WIDGET_SKILL.Succeeded())
	{
		skillWidgetClass = WIDGET_SKILL.Class;
	}

}

void ACJPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	playerState = Cast<ACJPlayerState>(PlayerState);
	
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly::FInputModeGameOnly());

}

void ACJPlayerController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

	shortcutWidget = CreateWidget<UCJShortcut>(this, shortcutWidgetClass);
	shortcutWidget->AddToViewport();
}

void ACJPlayerController::UnPossess()
{
	Super::UnPossess();
	if(shortcutWidget) shortcutWidget->RemoveFromParent();
	CJLOG(Warning, TEXT("Unpossess called"));
}

void ACJPlayerController::MouseCursorToggle()
{
	if(bShowMouseCursor) 
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	}
	else
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI::FInputModeGameAndUI());
	}
}

void ACJPlayerController::TurnOnCustomWidget()
{
	if (customKeyWidgetClass)
	{
		bShowMouseCursor = true;
		customKeyWidget = CreateWidget<UCJCustomKeyWidget>(this, customKeyWidgetClass);
		SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
		customKeyWidget->AddToViewport();
	}
	else
	{
		CJLOG(Warning, TEXT("CustomKeyWidgetClass not found"));
	}	
}

void ACJPlayerController::TurnOnSkillWidget()
{
	CJLOG(Warning, TEXT("LOG"));
	bShowMouseCursor = true;
	skillListWidget = CreateWidget<UCJSkillList>(this, skillListWidgetClass);
	SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
	skillListWidget->AddToViewport();

}