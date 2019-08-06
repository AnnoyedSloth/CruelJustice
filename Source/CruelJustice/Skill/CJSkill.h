// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "GameFramework/Actor.h"
#include "CJSkill.generated.h"

//DECLARE_MULTICAST_DELEGATE(IsSkillPlayEnded);

class ACJPlayer;

UCLASS()
class CRUELJUSTICE_API ACJSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACJSkill();

protected:

	UPROPERTY(VisibleAnywhere, Category = Status)
	class ACJPlayer* skillInstigator;

	UPROPERTY(VisibleAnywhere, Category = Status)
		FText skillName;
	
	class UCJPlayerAnimInstance* animInstance;

	UAnimMontage* skillMontage;

	UPROPERTY()
	UParticleSystemComponent* skillParticle;

	//IsSkillPlayEnded skillEndDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitSkill(ACJPlayer* owner);
	virtual void PlaySkill();
	virtual void ApplyImpact();
	FText GetSkillName() const { return skillName; }
};
