// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerController.h"
#include "Pawn/CJPlayer.h"
#include "UI/CJCustomKeyWidget.h"
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

}

void ACJPlayerController::MouseCursorToggle()
{
	SetInputMode(FInputModeGameAndUI::FInputModeGameAndUI());
	bShowMouseCursor ? bShowMouseCursor = false : bShowMouseCursor = true;
}

void ACJPlayerController::TurnOnCustomWidget()
{
	if (customKeyWidgetClass)
	{
		bShowMouseCursor = true;
		customKeyWidget = CreateWidget<UCJCustomKeyWidget>(this, customKeyWidgetClass);
		SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
		customKeyWidget->AddToViewport();
		customKeyWidget->SetController(this);
	}
	else
	{
		CJLOG(Warning, TEXT("CustomKeyWidgetClass not found"));
	}
}

