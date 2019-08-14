// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Blueprint/UserWidget.h"
#include "CJKeyPressCheck.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJKeyPressCheck : public UUserWidget
{
	GENERATED_BODY()

	class UTextBlock* curTextBlock;

public:

	virtual void NativeConstruct() override;

	void SetPressedKey(FText pressedText);
	
	
};
