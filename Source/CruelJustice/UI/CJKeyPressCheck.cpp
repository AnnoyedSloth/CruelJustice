// Fill out your copyright notice in the Description page of Project Settings.

#include "CJKeyPressCheck.h"
#include "Components/TextBlock.h"

void UCJKeyPressCheck::NativeConstruct()
{
	Super::NativeConstruct();

	curTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("InputText")));
}

void UCJKeyPressCheck::SetPressedKey(FText pressedText)
{
	if (!curTextBlock)
	{
		CJLOG(Warning, TEXT("Textblock missing"));
		return;
	}
	curTextBlock->SetText(pressedText);
}
