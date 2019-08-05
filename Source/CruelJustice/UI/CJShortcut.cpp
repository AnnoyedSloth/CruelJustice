// Fill out your copyright notice in the Description page of Project Settings.

#include "CJShortcut.h"
#include "Controller/CJPlayerController.h"

void UCJShortcut::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCJShortcut::SetController(ACJPlayerController* ownerController)
{
	if (ownerController)
	{
		playerController = ownerController;
	}
}

