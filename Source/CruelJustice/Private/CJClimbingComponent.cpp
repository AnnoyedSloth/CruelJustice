// Fill out your copyright notice in the Description page of Project Settings.

#include "CJClimbingComponent.h"
#include "Pawn/CJPlayer.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UCJClimbingComponent::UCJClimbingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		AM_CLIMB(TEXT("/Game/AM_Climb.AM_Climb"));
	if (AM_CLIMB.Succeeded())
	{
		climbingMontage = AM_CLIMB.Object;
	}

	pelvisSocket = "PelvisSocket";
	isHanging = false;
	isClimbingLedge = false;
	// ...
}

void UCJClimbingComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called when the game starts
void UCJClimbingComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ACJPlayer>(GetOwner());
	if (!player)
	{
		CJLOG(Warning, TEXT("Player is missing"));
		return;
	}

	animInstance = player->GetAnimInstance();
	if (!animInstance)
	{
		CJLOG(Warning, TEXT("AnimInstance is missing"));
		return;
	}
	
}


// Called every frame
void UCJClimbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ForwardTracer();
	//HeightTracer();
	// ...
}



void UCJClimbingComponent::ForwardTracer()
{
	if (!player) return;

	float traceLength = 150.0f;

	FVector actorLocation = player->GetActorLocation();
	FVector actorForward = player->GetActorForwardVector();

	FVector forwardOffset = FVector(actorForward.X * traceLength, actorForward.Y * traceLength, actorForward.Z);

	FHitResult hitResult;
	FCollisionQueryParams params;
	bool result = GetWorld()->SweepSingleByChannel(
		hitResult,
		actorLocation,
		actorLocation + forwardOffset,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(20.0f),
		params
	);

	if (result)
	{
		wallLocation = hitResult.Location;
		wallNormal = hitResult.Normal;
	}

	FColor color = result ? FColor::Green : FColor::Red;

#if ENABLE_DRAW_DEBUG
	DrawDebugCapsule(GetWorld(),
		actorLocation + forwardOffset * 0.5f,
		traceLength*0.5f,
		20.0f,
		FRotationMatrix::MakeFromZ(forwardOffset).ToQuat(),
		color,
		false
	);
#endif
}

void UCJClimbingComponent::HeightTracer()
{
	if (!player) return;

	FVector actorLocation = player->GetActorLocation();
	FVector start = FVector(actorLocation.X, actorLocation.Y, actorLocation.Z + 250.0f);
	FVector actorForward = player->GetActorForwardVector();

	start += actorForward * 70.0f;

	FVector end = FVector(start.X, start.Y, start.Z - 250.0f);

	FHitResult hitResult;
	FCollisionQueryParams params;
	bool result = GetWorld()->SweepSingleByChannel(
		hitResult,
		start,
		end,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(20.0f),
		params
	);

	if (result)
	{
		heightLocation = hitResult.Location;
		//CJLOG(Warning, TEXT("Height compare : %f"), 
		//player->GetMesh()->GetSocketLocation(pelvisSocket).Z - heightLocation.Z);
	}

	if (HipToLedge())
	{
		CJLOG(Warning, TEXT("Hip to ledge enabled"));
		if (!isHanging)
		{
			CJLOG(Warning, TEXT("Grab ledge activated"));
			GrabLedge();
			isClimbingLedge = true;
		}
	}

	FColor color = result ? FColor::Green : FColor::Red;

#if ENABLE_DRAW_DEBUG
	DrawDebugCapsule(GetWorld(),
		start + (end-start)*0.5f,
		125.0f,
		20.0f,
		FRotationMatrix::MakeFromX(actorForward).ToQuat(),
		color,
		false
	);
#endif
}

bool UCJClimbingComponent::HipToLedge()
{
	CJLOG(Warning, TEXT("%f"), player->GetMesh()->GetSocketLocation(pelvisSocket).Z - heightLocation.Z);
	return UKismetMathLibrary::InRange_FloatFloat(
		player->GetMesh()->GetSocketLocation(pelvisSocket).Z - heightLocation.Z,
		-70.0f,
		0,
		true,
		true
	);
}

void UCJClimbingComponent::GrabLedge()
{

	CJLOG(Warning, TEXT("GrabLedge Activated"));

	animInstance->GrabWall(true);
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	isHanging = true;
	isClimbingLedge = false;

	FVector targetLoc = FVector(wallNormal.X + wallLocation.X, wallNormal.Y + wallLocation.Y + 35.0f,
		heightLocation.Z - 120.0f);

	FRotator sourceRot = UKismetMathLibrary::MakeRotFromX(wallNormal);
	FRotator targetRot = FRotator(sourceRot.Pitch, sourceRot.Yaw - 180.0f, sourceRot.Roll);

	FLatentActionInfo actionInfo;
	actionInfo.UUID = GetUniqueID();
	actionInfo.Linkage = 0;
	actionInfo.CallbackTarget = this;
	actionInfo.ExecutionFunction = "StopPlayerAction";

	UKismetSystemLibrary::MoveComponentTo(
		player->GetCapsuleComponent(),
		targetLoc,
		targetRot,
		false, false,
		.13f,
		false,
		EMoveComponentAction::Move,
		actionInfo
	);

}

void UCJClimbingComponent::StopPlayerAction()
{
	CJLOG(Warning, TEXT("StopPlayerAction Activated"));
	player->GetCharacterMovement()->StopMovementImmediately();
}

void UCJClimbingComponent::UnGrab()
{
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	player->GetAnimInstance()->GrabWall(false);
	isHanging = false;
	isClimbingLedge = false;
}

void UCJClimbingComponent::ClimbLedge()
{
	player->GetAnimInstance()->PlayMontage(climbingMontage, 1.0f);
	isClimbingLedge = false;
	//isHanging = false;
}