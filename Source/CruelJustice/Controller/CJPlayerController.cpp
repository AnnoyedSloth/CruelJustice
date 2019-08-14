// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerController.h"
#include "Pawn/CJPlayer.h"
#include "UI/CJCustomKeyWidget.h"
#include "UI/CJShortcut.h"
#include "UI/CJSkillList.h"
#include "UI/CJSkillWidget.h"
#include "UI/CJKeyPressCheck.h"
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

	static ConstructorHelpers::FClassFinder<UCJKeyPressCheck>
		WIDGET_INPUT(TEXT("/Game/UI/InputCheck.InputCheck_C"));
	if (WIDGET_INPUT.Succeeded())
	{
		keyPressCheckClass = WIDGET_INPUT.Class;
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

void ACJPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//if (keyPressCheck && WasInputKeyJustPressed(EKeys::AnyKey))
	//{
	//	keyPressCheck->SetPressedKey();
	//}
}

bool ACJPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	bool isKeyDown = Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
	if (keyPressCheck)
	{
		keyPressCheck->SetPressedKey(Key.GetDisplayName());
	}
	return isKeyDown;
}


void ACJPlayerController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

	shortcutWidget = CreateWidget<UCJShortcut>(this, shortcutWidgetClass);
	shortcutWidget->AddToViewport();

	keyPressCheck = CreateWidget<UCJKeyPressCheck>(this, keyPressCheckClass);
	keyPressCheck->AddToViewport();
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