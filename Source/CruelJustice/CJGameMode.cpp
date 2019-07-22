// Fill out your copyright notice in the Description page of Project Settings.

#include "CJGameMode.h"
#include "Pawn/CJPlayer.h"
#include "Controller/CJPlayerController.h"
#include "CJPlayerState.h"

ACJGameMode::ACJGameMode()
{
	DefaultPawnClass = ACJPlayer::StaticClass();
	PlayerControllerClass = ACJPlayerController::StaticClass();
	PlayerStateClass = ACJPlayerState::StaticClass();

}

void ACJGameMode::PostLogin(APlayerController* playerController)
{
	Super::PostLogin(playerController);
}