// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/Character.h"
#include "CJBaseCharacter.generated.h"

UCLASS()
class CRUELJUSTICE_API ACJBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACJBaseCharacter();


	// For properties
private:


	// For methods
private:

	// For properties
protected:

	enum class ECharacterState : uint8
	{
		PREINIT,
		LOADING,
		READY,
		DEAD
	};
	ECharacterState currentState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetCharacterState(ECharacterState newState);
	// For methods

	
	// For properties
public:


	// For methods
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
