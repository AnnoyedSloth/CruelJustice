// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CJEnemyState.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API ACJEnemyState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		int32 dropExp;
	
public:
	
	
};
