// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayerController.h"
#include "Pawn/CJPlayer.h"
#include "CJPlayerState.h"


ACJPlayerController::ACJPlayerController()
{

}

void ACJPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	playerState = Cast<ACJPlayerState>(PlayerState);

}

void ACJPlayerController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

}
