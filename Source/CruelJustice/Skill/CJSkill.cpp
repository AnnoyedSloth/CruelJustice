// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkill.h"
#include "Pawn/CJPlayer.h"


// Sets default values
ACJSkill::ACJSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//owner = skillOwner;
	//animInstance = Cast<UCJPlayerAnimInstance>(owner->GetAnimInstance());

	skillParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));

}

// Called when the game starts or when spawned
void ACJSkill::BeginPlay()
{
	Super::BeginPlay();

}

void ACJSkill::InitSkill(ACJPlayer* newOwner)
{
	owner = newOwner;
	animInstance = owner->GetAnimInstance();
}

// Called every frame
void ACJSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACJSkill::PlaySkill()
{

}

void ACJSkill::ApplyImpact()
{

}