// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkillWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/CJPlayerController.h"
#include "Pawn/CJPlayer.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "Skill/CJSkill.h"
#include "Skill/CJPlayerSkill1_Slash.h"
#include "UI/CJSkillDragDropOperation.h"
#include "WidgetBlueprintLibrary.h"

void UCJSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetDesiredSizeInViewport(FVector2D(200, 50));
	//this->SetRenderTransform(FWidgetTransform());

	//skillButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill")));
	skillName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillName")));

	if (!skillName)
	{
		skillName = NewObject<UTextBlock>();
		//CJLOG(Warning, TEXT("skillName not exist therefore spawned"));
	}

	if(skillPtr) skill = GetWorld()->SpawnActor<ACJSkill>(skillPtr);

	if (skill)
	{
		skillName->SetText(skill->GetSkillName());
		skill->skillInstigator = Cast<ACJPlayer>(GetOwningPlayerPawn());
		skill->animInstance = skill->skillInstigator->GetAnimInstance();
		//CJLOG(Warning, TEXT("%s"), *skill->GetSkillName().ToString());
	}
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
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//CJLOG(Warning, TEXT("Click detected"));
	
	//UDragDropOperation* operation;
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		//FReply::Handled().DetectDrag(this, EKeys::LeftMouseButton);
		//NativeOnDragDetected(InGeometry, InMouseEvent, operation);
	}

	return reply.NativeReply;
}

void UCJSkillWidget::SetupSkillInfo(ACJSkill* otherSkill)
{
	skill = otherSkill;
	if (skill)
	{
		//skillName->SetText(text);
		skill->skillInstigator = Cast<ACJPlayer>(GetOwningPlayerPawn());
		skill->animInstance = skill->skillInstigator->GetAnimInstance();
		//CJLOG(Warning, TEXT("%s"), *skill->GetSkillName().ToString());
	}
}

void UCJSkillWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	ACJPlayerController* controller = Cast<ACJPlayerController>(GetOwningPlayer());
	//controller->skillWidget = CreateWidget<UCJSkillWidget>(controller, controller->skillWidgetClass);
	//controller->skillWidget->AddToViewport();
	if (controller)
	{
		controller->skillWidget = CreateWidget<UCJSkillWidget>(controller, controller->skillWidgetClass);
		controller->skillWidget->SetupSkillInfo(skill);


		//CJLOG(Warning, TEXT("%s"), *controller->skillWidget->skillName->GetText().ToString());
		//CJLOG(Warning, TEXT("%s"), *this->skillName->GetText().ToString());
		
		
		//controller->skillWidget->AddToViewport();
		UCJSkillDragDropOperation* oper = NewObject<UCJSkillDragDropOperation>();
		oper->skill = skill;
		if (skillPtr)
		{
			oper->skillPtr = skillPtr;
		}

		oper->name = skillName->GetText();
		OutOperation = oper;
		OutOperation->DefaultDragVisual = controller->skillWidget;
	
	}
	else
	{
		CJLOG(Warning, TEXT("Controller missing"));
	}
	//CJLOG(Warning, TEXT("Drag detected"));
}

bool UCJSkillWidget::NativeOnDrop(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UCJSkillDragDropOperation* operation = Cast<UCJSkillDragDropOperation>(InOperation);
	this->skill = operation->skill;
	this->skillPtr = operation->skillPtr;
	this->skillName->SetText(operation->name);
	this->SetupSkillInfo(operation->skill);

	CJLOG(Warning, TEXT("%s"), *operation->name.ToString());
	//CJLOG(Warning, TEXT("%s"), *skillName->GetText().ToString());
	//CJLOG(Warning, TEXT("%s"), *this->skillName->GetText().ToString());

	return true;
}

void UCJSkillWidget::Play()
{
	ACJPlayer* player = Cast<ACJPlayer>(GetOwningPlayerPawn());
	if (!player)
	{
		CJLOG(Warning, TEXT("Player missing"));
		return;
	}
	if (!skillPtr)
	{
		CJLOG(Warning, TEXT("SkillPtr missing"));
		return;
	}

	if (player->GetIsAttacking()) return;
	player->SetIsAttacking(true);

	ACJSkill* newSkill = GetWorld()->SpawnActor<ACJSkill>(skillPtr,
		player->GetActorLocation(), player->GetActorRotation());
	newSkill->InitSkill(player);
	newSkill->PlaySkill();
}