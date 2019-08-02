// Fill out your copyright notice in the Description page of Project Settings.

#include "CJCustomKeyWidget.h"
#include "Components/Button.h"
#include "Controller/CJPlayerController.h"


void UCJCustomKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bCanEverTick = false;

	moveForward = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveForward")));
	moveBack = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveBack")));
	moveLeft = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveLeft")));
	moveRight = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveRight")));
	attack = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Attack")));
	skill1 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill1")));
	skill2 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill2")));
	evade = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Evade")));
	ok = Cast<UButton>(GetWidgetFromName(TEXT("Btn_OK")));

	ok->OnReleased.AddDynamic(this, &UCJCustomKeyWidget::Close);
}

void UCJCustomKeyWidget::SetController(ACJPlayerController* ownerController)
{
	if (ownerController)
	{
		playerController = ownerController;
	}
}

void UCJCustomKeyWidget::NativeTick(const FGeometry &myGeometry, float inDeltaTime)
{
	Super::NativeTick(myGeometry, inDeltaTime);

	TArray<FKey> keys;
	EKeys::GetAllKeys(keys);

	for (FKey key : keys) 
	{
		if (key == EKeys::P) continue;
		if (playerController->IsInputKeyDown(key))
		{
			CJLOG(Warning, *key.GetFName().ToString());
		}
	}
}

void UCJCustomKeyWidget::Close()
{
	playerController->bShowMouseCursor = false;
	playerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	RemoveFromParent();
	//RemoveFromViewport();

}

