// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CJPlayerState.generated.h"

/**
 * 
 */

class ACJPlayer;

UCLASS()
class CRUELJUSTICE_API ACJPlayerState : public APlayerState
{
	GENERATED_BODY()

	friend ACJPlayer;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		float maxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		float maxMP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		float hp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		float mp;

public:
	ACJPlayerState();
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void UpdatePlayerStat(int32 level);

	UFUNCTION()
		void ApplyDamage(float deltaHP);
};
