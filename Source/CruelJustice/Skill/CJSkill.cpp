// Fill out your copyright notice in the Description page of Project Settings.

#include "CJSkill.h"


// Sets default values
ACJSkill::ACJSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//skillParticle = CreateDefaultSubobject<UParticleSystem>(FName("Particle"));

}

// Called when the game starts or when spawned
void ACJSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACJSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

