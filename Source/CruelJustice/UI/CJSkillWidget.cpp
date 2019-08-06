// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkillWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/CJPlayerController.h"
#include "Skill/CJSkill.h"
#include "WidgetBlueprintLibrary.h"

void UCJSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetDesiredSizeInViewport(FVector2D(200, 50));
	//this->SetRenderTransform(FWidgetTransform());

	//skillButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill")));
	skillName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillName")));

	//skill = NewObject<ACJSkill>(skillPtr);

	//if (skill)
	//{
	//	skillName->SetText(skill->GetSkillName());
	//	CJLOG(Warning, TEXT("%s"), *skill->GetSkillName().ToString());
	//}
}

void UCJSkillWidget::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry, deltaTime);

	//float x, y;
	//GetOwningPlayer()->GetMousePosition(x, y);

	//FWidgetTransform widgetTransform;
	//widgetTransform.Translation = FVector2D(x, y);

	//this->SetRenderTranslation(widgetTransform.Translation);

}

FReply UCJSkillWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//CJLOG(Warning, TEXT("Click detected"));
	//UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	UDragDropOperation* operation;
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		//FReply::Handled().DetectDrag(this, EKeys::LeftMouseButton);
		NativeOnDragDetected(InGeometry, InMouseEvent, operation);
	}

	return OnPreviewMouseButtonDown(InGeometry, InMouseEvent).NativeReply;

}

void UCJSkillWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//OutOperation->Payload
	ACJPlayerController* controller = Cast<ACJPlayerController>(GetOwningPlayer());
	//controller->skillWidget = CreateWidget<UCJSkillWidget>(controller, controller->skillWidgetClass);
	//controller->skillWidget->AddToViewport();
	if (controller)
	{
		controller->skillWidget = CreateWidget<UCJSkillWidget>(GetOwningPlayer(), controller->skillWidgetClass);
		//DuplicateObject(this, controller->skillWidget);
		controller->skillWidget->AddToViewport();
	
	}
	else
	{
		CJLOG(Warning, TEXT("Controller missing"));
	}
	OutOperation->DefaultDragVisual = controller->skillWidget;

	CJLOG(Warning, TEXT("Drag detected"));

	return OnDragDetected(InGeometry, InMouseEvent, OutOperation);
}