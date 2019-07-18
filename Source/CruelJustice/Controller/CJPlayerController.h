// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/PlayerController.h"
#include "CJPlayerController.generated.h"

/**
 * 
 */

class ACJPlayerState;

UCLASS()
class CRUELJUSTICE_API ACJPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	ACJPlayerState* playerState;

public:
	ACJPlayerController();
	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* pawn) override;

	
	
};
