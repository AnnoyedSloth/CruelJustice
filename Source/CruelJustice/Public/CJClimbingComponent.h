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

	UPROPERTY(VisibleAnywhere, Category = AnimMontage, meta = (AllowPrivateAccess = true))
	UAnimMontage* climbingMontage;

	FVector leftMoveCheck;
	FVector rightMoveCheck;

	FVector leftJumpCheck;
	FVector rightJumpCheck;

	UPROPERTY(VisibleAnywhere, Category = Ledge)
	bool canMoveLeft;

	UPROPERTY(VisibleAnywhere, Category = Ledge)
	bool canMoveRight;

	UPROPERTY(VisibleAnywhere, Category = Ledge)
	bool canJumpLeft;
	
	UPROPERTY(VisibleAnywhere, Category = Ledge)
	bool canJumpRight;

private:

	void ForwardTracer();

	bool HipToLedge();

	void CheckHorizontalMove();
	void CheckHorizontalJump();

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

	void HeightTracer();

	void GrabLedge();
	void UnGrab();
	void ClimbLedge();
	void MoveInLedge();

	bool GetIsHanging() { return isHanging; }
	bool GetIsClimbing() { return isClimbingLedge; }
	bool GetCanMoveLeft() { return canMoveLeft; }
	bool GetCanMoveRight() { return canMoveRight; }
};
