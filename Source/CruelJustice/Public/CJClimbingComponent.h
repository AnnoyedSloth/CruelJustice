// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CruelJustice.h"
#include "Components/SceneComponent.h"
#include "CJClimbingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRUELJUSTICE_API UCJClimbingComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	class ACJPlayer* player;
	class UCJPlayerAnimInstance* animInstance;
	FVector wallLocation;
	FVector heightLocation;
	FVector wallNormal;
	FName pelvisSocket;

	bool isClimbingLedge;
	bool isHanging;

private:

	void ForwardTracer();
	void HeightTracer();

	bool HipToLedge();

	UFUNCTION()
	void StopPlayerAction();

public:	
	// Sets default values for this component's properties
	UCJClimbingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GrabLedge();

};
