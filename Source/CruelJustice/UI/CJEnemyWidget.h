// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CJEnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJEnemyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class ACJEnemy* enemy);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
	
private:
	TWeakObjectPtr<class ACJEnemy> currentEnemy;

	class UProgressBar* hpProgressBar;
	
};
