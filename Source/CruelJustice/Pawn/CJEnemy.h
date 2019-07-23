// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Pawn/CJBaseCharacter.h"
#include "CJEnemy.generated.h"

/**
 * 
 */

UCLASS()
class CRUELJUSTICE_API ACJEnemy : public ACJBaseCharacter
{
	GENERATED_BODY()

	// For properties
protected:

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float maxHP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float maxMP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float hp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float mp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float attack;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float defense;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	int dropExp;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* hpWidget;

	class UCJMonsterAnimInstance* animInstance;

	UAnimMontage* deadAnim;
protected:
	virtual void BeginPlay() override;
	
public:
	ACJEnemy();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float deltaTime) override;
	void InitStatData(int32 monsterID);

	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent,
		class AController* eventInstigator, AActor* damageCauser) override;

	UFUNCTION()
		float GetHPRatio();


	// Set up as pure virtual function to prevent instanciation
	//virtual void Attack() = 0;
	
};
