// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkillList.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/CJPlayerController.h"

void UCJSkillList::NativeConstruct()
{
	Super::NativeConstruct();

	bCanEverTick = false;

	skills.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Slash"))));
	skills.Add(Cast<UButton>(GetWidgetFromName(TEXT("Btn_Fireball"))));

}

void UCJSkillList::SetController(ACJPlayerController* ownerController)
{
	if (ownerController)
	{
		playerController = ownerController;
	}
}


FReply UCJSkillList::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);

	const FKey key = InKeyEvent.GetKey();
	if (key == EKeys::K)
	{
		playerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
		RemoveFromParent();
	}
	return OnKeyDown(InGeometry, InKeyEvent).NativeReply;
}

