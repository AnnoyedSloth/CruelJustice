// Fill out your copyright notice in the Description page of Project Settings.

#include "CJBaseCharacter.h"


// Sets default values
ACJBaseCharacter::ACJBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = GetMesh();
	mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

}

// Called when the game starts or when spawned
void ACJBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACJBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACJBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACJBaseCharacter::SetCharacterState(ECharacterState newState)
{
	CJCHECK(currentState != newState);

	switch (newState)
	{
	case ECharacterState::LOADING:
		
		SetActorHiddenInGame(true);
		bCanBeDamaged = false;
		break;

	case ECharacterState::READY:

		SetActorHiddenInGame(false);
		bCanBeDamaged = true;

		// ��� ���� ���ٽ� �߰�

		// 1��Ī ĳ������ ��� UMG �߰�
		// 3��Ī ĳ������ ��� ü�¹� �߰�

		break;

	case ECharacterState::DEAD:

		SetActorEnableCollision(false);

	}

}
