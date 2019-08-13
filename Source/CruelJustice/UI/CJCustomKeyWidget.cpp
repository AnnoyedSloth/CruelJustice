// Fill out your copyright notice in the Description page of Project Settings.

#include "CJCustomKeyWidget.h"
#include "Pawn/CJPlayer.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"


void UCJCustomKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bCanEverTick = false;

	curTextBlock = nullptr;

	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveForward"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveBack"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveLeft"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_MoveRight"))));
	buttons.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Evade"))));
	ok = Cast<UButton>(GetWidgetFromName(TEXT("Btn_OK")));

	textBlocks.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Forward"))));
	textBlocks.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Backward"))));
	textBlocks.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Left"))));
	textBlocks.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Right"))));
	textBlocks.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("BtnText_Evade"))));

	for (UButton* button : buttons)
	{
		button->OnReleased.AddDynamic(this, &UCJCustomKeyWidget::ButtonClicked);
	}
	

	ok->OnReleased.AddDynamic(this, &UCJCustomKeyWidget::Close);
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
	const UInputSettings* inputSettings = GetDefault<UInputSettings>();
	UInputComponent* inputComponent = GetOwningPlayer()->GetPawn()->InputComponent;
	
	//inputComponent->ClearActionBindings();
	TArray<FInputAxisKeyMapping> keyMappings;
	inputSettings->GetAxisMappingByName("MoveForward", keyMappings);
	inputSettings->GetAxisMappingByName("MoveRight", keyMappings);
	for (FInputAxisKeyMapping mapping : keyMappings)
	{
		((UInputSettings*)inputSettings)->RemoveAxisMapping(mapping);
	}

	TArray<FInputActionKeyMapping> actionMappings;
	inputSettings->GetActionMappingByName("Roll", actionMappings);
	
	for (FInputActionKeyMapping action : actionMappings)
	{
		((UInputSettings*)inputSettings)->RemoveActionMapping(action);
	}

	for (int a = 0; a < buttons.Num(); ++a)
	{
		switch (a)
		{
		case 0:
		{
			const FInputAxisKeyMapping axisMapping(FName("MoveForward"), FKey(FName(*textBlocks[a]->GetText().ToString())), 1);
			((UInputSettings*)inputSettings)->AddAxisMapping(axisMapping);
		}
			break;
		case 1:
		{
			const FInputAxisKeyMapping axisMapping(FName("MoveForward"), FKey(FName(*textBlocks[a]->GetText().ToString())), -1);
			((UInputSettings*)inputSettings)->AddAxisMapping(axisMapping);
		}
			break;
		case 2:
		{
			const FInputAxisKeyMapping axisMapping(FName("MoveRight"), FKey(FName(*textBlocks[a]->GetText().ToString())), -1);
			((UInputSettings*)inputSettings)->AddAxisMapping(axisMapping);
		}
		break;
		case 3:
		{
			const FInputAxisKeyMapping axisMapping(FName("MoveRight"), FKey(FName(*textBlocks[a]->GetText().ToString())), 1);
			((UInputSettings*)inputSettings)->AddAxisMapping(axisMapping);
		}
		break;
		case 4:
		{
			const FInputActionKeyMapping actionMapping(
				FName("Roll"), FKey(FName(*textBlocks[a]->GetText().ToString())),
				false, false, false, false);
			((UInputSettings*)inputSettings)->AddActionMapping(actionMapping);
		}
		break;
		default:
			break;
		}
	}

	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	RemoveFromParent();
	//RemoveFromViewport();
}

//void UCJCustomKeyWidget::ReceiveKey()
//{
//	FGeometry geometry;
//	FKeyEvent key;
//	OnKeyDown(geometry, key);
//}

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

	CJLOG(Warning, TEXT("%s"), *InKeyEvent.GetKey().GetFName().ToString());

	if (curTextBlock)
	{
		curTextBlock->SetText(key.GetDisplayName());
	}
	curTextBlock = nullptr;

	return OnKeyDown(InGeometry, InKeyEvent).NativeReply;
}

FReply UCJCustomKeyWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply reply = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

	const FKey key = InKeyEvent.GetKey();

	if (key == EKeys::SpaceBar || key == EKeys::Up || key==EKeys::Down || key==EKeys::Left || key==EKeys::Right)
	{
		if (curTextBlock)
		{
			curTextBlock->SetText(key.GetDisplayName());
		}
		curTextBlock = nullptr;
	}

	return reply;
}

FReply UCJCustomKeyWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	const FKey key = InMouseEvent.GetEffectingButton();

	if (curTextBlock)
	{
		curTextBlock->SetText(key.GetDisplayName());
	}
	curTextBlock = nullptr;
	
	
	return reply;
}