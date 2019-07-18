// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/GameMode.h"
#include "CJGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ACJGameMode();
	
	virtual void PostLogin(APlayerController* playerController) override;
	
};
