// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemyWidget.h"
#include "Pawn/CJEnemy.h"
#include "Components/ProgressBar.h"

void UCJEnemyWidget::BindCharacterStat(ACJEnemy* newCharacter)
{
	currentCharacter = newCharacter;

	currentCharacter->onHPChanged.AddUObject(this, &UCJEnemyWidget::UpdateHPWidget);

}

void UCJEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	hpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	CJCHECK(hpProgressBar != nullptr);
	UpdateHPWidget();
}

void UCJEnemyWidget::UpdateHPWidget()
{
	if (currentCharacter.IsValid())
	{
		if (hpProgressBar)
		{
			hpProgressBar->SetPercent(currentCharacter->GetHPRatio());
		}
	}
}

