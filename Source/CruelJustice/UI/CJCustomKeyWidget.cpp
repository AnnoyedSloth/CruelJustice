// Fill out your copyright notice in the Description page of Project Settings.

#include "CJCustomKeyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/CJPlayerController.h"


void UCJCustomKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bCanEverTick = false;

	curTextBlock = nullptr;

	//moveForward = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveForward")));
	//moveBack = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveBack")));
	//moveLeft = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveLeft")));
	//moveRight = Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveRight")));
	//attack = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Attack")));
	//skill1 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill1")));
	//skill2 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill2")));
	//evade = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Evade")));
	//ok = Cast<UButton>(GetWidgetFromName(TEXT("Btn_OK")));
	//buttons.Reserve(7);
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveForward"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveBack"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveLeft"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveRight"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Attack"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill1"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill2"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Evade"))));
	ok = Cast<UButton>(GetWidgetFromName(TEXT("Btn_OK")));

	text_Forward = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Forward")));
	text_Backward = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Backward")));
	text_Left = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Left")));
	text_Right = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Right")));
	text_Attack = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Attack")));
	text_Skill1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Skill1")));
	text_Skill2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Skill2")));
	text_Evade = Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Evade")));

	for (UButton* button : buttons)
	{
		button->OnReleased.AddDynamic(this, &UCJCustomKeyWidget::ButtonClicked);
	}
	

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

	//TArray<FKey> keys;
	//EKeys::GetAllKeys(keys);

	//for (FKey key : keys) 
	//{
	//	if (key == EKeys::P) continue;
	//	if (playerController->IsInputKeyDown(key))
	//	{
	//		CJLOG(Warning, *key.GetFName().ToString());
	//	}
	//}
	
}

void UCJCustomKeyWidget::Close()
{
	playerController->bShowMouseCursor = false;
	playerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	RemoveFromParent();
	//RemoveFromViewport();
}

void UCJCustomKeyWidget::ReceiveKey()
{
	FGeometry geometry;
	FKeyEvent key;
	OnKeyDown(geometry, key);

}

void UCJCustomKeyWidget::ButtonClicked()
{
	UButton* curButton = GetEnabledButton();
	curTextBlock = Cast<UTextBlock>(curButton->GetChildAt(0));
}

UButton* UCJCustomKeyWidget::GetEnabledButton()
{
	for (UButton* button : buttons)
	{
		if (button->HasKeyboardFocus())
		{
			CJLOG(Warning, TEXT("%s"), *button->GetFName().ToString());
			return button;
		}
	}
	return nullptr;
}

FReply UCJCustomKeyWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	CJLOG(Warning, TEXT("Pressed key is %d"), InKeyEvent.GetCharacter());

	const FKey key = InKeyEvent.GetKey();

	if (curTextBlock)
	{
		curTextBlock->SetText(key.GetDisplayName());
	}

	return OnKeyDown(InGeometry, InKeyEvent).NativeReply;
}