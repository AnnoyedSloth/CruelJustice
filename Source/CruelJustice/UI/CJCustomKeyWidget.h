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

	TArray<class UButton*> buttons;
	//class UButton* moveForward;
	//class UButton* moveBack;
	//class UButton* moveLeft;
	//class UButton* moveRight;
	//class UButton* attack;
	//class UButton* skill1;
	//class UButton* skill2;
	//class UButton* evade;
	class UButton* ok;

	class UTextBlock* text_Forward;
	class UTextBlock* text_Backward;
	class UTextBlock* text_Left;
	class UTextBlock* text_Right;
	class UTextBlock* text_Attack;
	class UTextBlock* text_Skill1;
	class UTextBlock* text_Skill2;
	class UTextBlock* text_Evade;

	FString clickedName;
	UTextBlock* curTextBlock;

	UFUNCTION()
		UButton* GetEnabledButton();

protected:
	
	virtual void NativeConstruct() override;
	//virtual void Tick() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnKeyDown(
		const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	
public:	
	UFUNCTION()
	void Close();

	UFUNCTION()
		void ButtonClicked();

	void SetController(ACJPlayerController* ownerController);
	void ReceiveKey();

};
