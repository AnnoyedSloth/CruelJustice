// Fill out your copyright notice in the Description page of Project Settings.

#include "CJGameMode.h"
#include "Pawn/CJPlayer.h"
#include "Controller/CJPlayerController.h"

ACJGameMode::ACJGameMode()
{
	DefaultPawnClass = ACJPlayer::StaticClass();
	PlayerControllerClass = ACJPlayerController::StaticClass();

}

void ACJGameMode::PostLogin(APlayerController* playerController)
{
	Super::PostLogin(playerController);
}