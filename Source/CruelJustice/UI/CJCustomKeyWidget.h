// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Blueprint/UserWidget.h"
#include "CJCustomKeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUELJUSTICE_API UCJCustomKeyWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	class ACJPlayerController* playerController;

	class UButton* moveForward;
	class UButton* moveBack;
	class UButton* moveLeft;
	class UButton* moveRight;
	class UButton* attack;
	class UButton* skill1;
	class UButton* skill2;
	class UButton* evade;
	class UButton* ok;

protected:
	
	virtual void NativeConstruct() override;
	//virtual void Tick() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

	
public:	
	UFUNCTION()
	void Close();

	void SetController(ACJPlayerController* ownerController);

};
