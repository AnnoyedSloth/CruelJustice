// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CJShortcut.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJShortcut : public UUserWidget
{
	GENERATED_BODY()

private:
	class ACJPlayerController* playerController;
	
public:
	virtual void NativeConstruct() override;

	
	
};
