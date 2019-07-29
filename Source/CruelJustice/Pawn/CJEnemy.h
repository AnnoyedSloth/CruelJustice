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

	// Status informations
	UPROPERTY(VisibleAnywhere, Category = Stat)
		float maxHP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float maxMP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float hp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float mp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		float defense;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		int dropExp;

	// Components

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* hpWidget;

	UPROPERTY(VisibleAnywhere, Category = AI, meta = (AllowPrivateAccess = true))
		class UPawnSensingComponent* pawnSensingComp;

	// Etc

	UPROPERTY(VisibleAnywhere, Category = Animation)
		class UCJEnemyAnimInstance* animInstance;

	UPROPERTY(VisibleAnywhere, Category = Animation)
		UAnimMontage* deadAnim;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class ACJEnemyAIController* enemyAIController;

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

	UFUNCTION()
		virtual void AttackMontagePlay();

	UFUNCTION()
		virtual void Attack();

	UFUNCTION()
		virtual void PlayerCaught(APawn* pawn);


	// Set up as pure virtual function to prevent instanciation
	//virtual void Attack() = 0;
	
};
