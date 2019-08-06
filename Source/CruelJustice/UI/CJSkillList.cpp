// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkillList.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/CJPlayerController.h"
#include "UI/CJSkillWidget.h"
#include "ConstructorHelpers.h"

void UCJSkillList::NativeConstruct()
{
	Super::NativeConstruct();

	bCanEverTick = false;

	skills.Add(Cast<UCJSkillWidget>(GetWidgetFromName(TEXT("Slash"))));
	skills.Add(Cast<UCJSkillWidget>(GetWidgetFromName(TEXT("Fireball"))));

	closeButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Close")));

	closeButton->OnReleased.AddDynamic(this, &UCJSkillList::Close);

	bIsFocusable = true;

	//skills[0]->OnPressed.AddDynamic(this, &UCJSkillList::Skill1);
	//skills[1]->OnPressed.AddDynamic(this, &UCJSkillList::Skill2);

}

FReply UCJSkillList::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);
	const FKey key = InKeyEvent.GetKey();
	if (key == EKeys::K)
	{
		//RemoveFromParent();
		CJLOG(Warning, TEXT("Pressed key is %d"), InKeyEvent.GetCharacter());
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	}
	return OnKeyDown(InGeometry, InKeyEvent).NativeReply;
}

void UCJSkillList::Close()
{
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	GetOwningPlayer()->bShowMouseCursor = false;
	RemoveFromParent();
}

void UCJSkillList::Skill1()
{
	ACJPlayerController* playerController = Cast<ACJPlayerController>(GetOwningPlayer());
	playerController->skillWidget = CreateWidget<UCJSkillWidget>(GetOwningPlayer(), playerController->skillWidgetClass);
	playerController->skillWidget->AddToViewport();
}

void UCJSkillList::Skill2()
{
	ACJPlayerController* playerController = Cast<ACJPlayerController>(GetOwningPlayer());
	playerController->skillWidget = CreateWidget<UCJSkillWidget>(GetOwningPlayer(), playerController->skillWidgetClass);
	playerController->skillWidget->AddToViewport();
}