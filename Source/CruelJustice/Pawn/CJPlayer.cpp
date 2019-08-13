// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayer.h"
#include "Controller/CJPlayerController.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "Skill/CJSkill.h"
#include "Skill/CJPlayerSkill1_Slash.h"
#include "Skill/CJPlayerSkill2_Fireball.h"
#include "CJPlayerState.h"
#include "CJGameInstance.h"
#include "UI/CJShortcut.h"
#include "UI/CJSkillWidget.h"
#include "CJClimbingComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

ACJPlayer::ACJPlayer()
{
	// Create Components
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	lvUpParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LvUpParticle"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC"));
	if (SK_MESH.Succeeded())
	{
		mesh->SetSkeletalMesh(SK_MESH.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		BP_ANIM(TEXT("/Game/Animation/1_Player/BP_Player_Anim.BP_Player_Anim_C"));
	if (BP_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_LVUP(TEXT("/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Resurrection/P_Resurrection.P_Resurrection"));
	if (PS_LVUP.Succeeded())
	{
		lvUpParticle->SetTemplate(PS_LVUP.Object);
		lvUpParticle->bAutoActivate = false;
	}
	
	climbingComponent = CreateDefaultSubobject<UCJClimbingComponent>(TEXT("ClimbingComponeng"));


	// Setup hierarchy structure
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	mesh->SetupAttachment(RootComponent);
	lvUpParticle->SetupAttachment(RootComponent);
	climbingComponent->SetupAttachment(RootComponent);

	// Initialize created component's specific options
	springArm->TargetArmLength = 400.0f;
	springArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	springArm->bUsePawnControlRotation = true;
	springArm->bInheritPitch = true;
	springArm->bInheritRoll = true;
	springArm->bInheritYaw = true;
	springArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	capsule->SetCollisionProfileName(TEXT("Player"));
	lvUpParticle->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

	attackRange = 150;
	attackRadius = 80;

	currentCombo = 1;
	recoveryCombo = 1;
	level = 1;
}

void ACJPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	animInstance = Cast<UCJPlayerAnimInstance>(mesh->GetAnimInstance());

	animInstance->OnMontageEnded.AddDynamic(this, &ACJPlayer::OnAttackMontageEnded);

	// 기본 콤보 공격시 공격 타이밍 관련 델리게이트 바인딩
	animInstance->onAttackHitCheck.AddUObject(this, &ACJPlayer::AttackCheck);

	// 다음 콤보 공격으로 연계 관련 델리게이트 바인딩
	animInstance->onNextAttackCheck.AddLambda([this]() -> void {

		//ABLOG(Warning, TEXT("OnNextAttackCheck"))
		//canNextCombo = false;

		if (isAttacking)
		{
			FVector viewLocation;
			FRotator viewRotation;
			GetActorEyesViewPoint(viewLocation, viewRotation);
			viewRotation.Roll = 0;
			viewRotation.Pitch = 0;
			SetActorRotation(viewRotation);

			//ABLOG(Warning, TEXT("currentCombo = %d"), currentCombo);
			//SetActorRotation(FMath::RInterpTo(GetActorRotation(), viewRotation, GetWorld()->GetDeltaSeconds(), 2.0f));

			AttackStartComboState();
			animInstance->JumpToAttackMontageSection(currentCombo);
			//CJLOG(Warning, TEXT("Current Combo num : %d"), currentCombo);

		}
		else
		{
			animInstance->JumpToRecoveryMontageSection(recoveryCombo);
			//CJLOG(Warning, TEXT("Current Combo num : %d"), recoveryCombo);
		}
	});


}

void ACJPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<ACJPlayerController>(GetController());
	playerState = Cast<ACJPlayerState>(PlayerState);
	if (!playerState) CJLOG(Warning, TEXT("Player state missing"));

	// Setup Initial level when start game
	auto gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	if (!gameInstance) CJLOG(Warning, TEXT("GameInstance missing"));
	

	playerState->maxHP = gameInstance->GetPlayerStatData(level)->maxHP;
	playerState->maxMP = gameInstance->GetPlayerStatData(level)->maxMP;
	attack = playerState->attack = gameInstance->GetPlayerStatData(level)->attack;

	curExp = gameInstance->GetPlayerStatData(level)->curExp;
	nextExp = gameInstance->GetPlayerStatData(level)->nextExp;
}

void ACJPlayer::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


}

void ACJPlayer::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);
}

void ACJPlayer::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);



	playerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACJPlayer::MoveForward);
	playerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACJPlayer::MoveRight);
	playerInputComponent->BindAxis(TEXT("Turn"), this, &ACJPlayer::Turn);
	playerInputComponent->BindAxis(TEXT("LookUp"), this, &ACJPlayer::LookUp);

	playerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACJPlayer::Jump);
	playerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ACJPlayer::Attack);
	playerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ACJPlayer::AttackEnd);
	playerInputComponent->BindAction(TEXT("Roll"), IE_Pressed, this, &ACJPlayer::Dodge);

	playerInputComponent->BindAction(TEXT("Key1"), IE_Pressed, this, &ACJPlayer::Key1);
	playerInputComponent->BindAction(TEXT("Key2"), IE_Pressed, this, &ACJPlayer::Key2);
	playerInputComponent->BindAction(TEXT("Key3"), IE_Pressed, this, &ACJPlayer::Key3);
	playerInputComponent->BindAction(TEXT("Key4"), IE_Pressed, this, &ACJPlayer::Key4);
	playerInputComponent->BindAction(TEXT("Key5"), IE_Pressed, this, &ACJPlayer::Key5);

	playerInputComponent->BindKey(EKeys::LeftAlt, IE_Pressed, this, &ACJPlayer::ToggleCursor);
	playerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &ACJPlayer::TurnOnKeyUI);
	playerInputComponent->BindKey(EKeys::K, IE_Pressed, this, &ACJPlayer::TurnOnSkillWidget);
	playerInputComponent->BindKey(EKeys::F, IE_Pressed, this, &ACJPlayer::UnGrab);
}

void ACJPlayer::MoveForward(float value)
{
	if (climbingComponent->GetIsHanging()) return;
	if(!isAttacking) AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), value);
}

void ACJPlayer::MoveRight(float value)
{
	if (climbingComponent->GetIsHanging())
	{
		climbingComponent->MoveInLedge();
		return;
	}
	if (!isAttacking) AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), value);
}

void ACJPlayer::Turn(float value)
{
	AddControllerYawInput(value);
}

void ACJPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ACJPlayer::Jump()
{
	if (climbingComponent->GetIsHanging())
	{
		if (climbingComponent->GetCanJumpLeft() || climbingComponent->GetCanJumpRight())
		{
			climbingComponent->JumpLedge();
		}
		else climbingComponent->ClimbLedge();
	}
	else Super::Jump();

	//if (GetCharacterMovement()->IsFalling()) climbingComponent->HeightTracer();
	if (GetCharacterMovement()->IsFalling()) climbingComponent->GrabWall();
}

void ACJPlayer::Attack()
{
	if (isAttacking) return;
	
	FVector viewLocation;
	FRotator viewRotation;
	GetActorEyesViewPoint(viewLocation, viewRotation);
	viewRotation.Roll = 0;
	viewRotation.Pitch = 0;
	SetActorRotation(viewRotation);

	animInstance->PlayAttackMontage();
	isAttacking = true;
	
}

void ACJPlayer::Dodge()
{
	FVector viewLocation;
	FRotator viewRotation;
	GetActorEyesViewPoint(viewLocation, viewRotation);
	viewRotation.Roll = 0;
	viewRotation.Pitch = 0;
	SetActorRotation(viewRotation);

	animInstance->PlayRollMontage();
}

void ACJPlayer::AttackEnd()
{
	recoveryCombo = currentCombo;
	isAttacking = false;
	currentCombo = 1;	
}

void ACJPlayer::AttackStartComboState()
{
	currentCombo = FMath::Clamp<int32>(currentCombo + 1, 1, 4);
}

void ACJPlayer::OnAttackMontageEnded(UAnimMontage* montage, bool isInterrupted)
{
	//CJLOG(Warning, TEXT("Attack ended"));

	isAttacking = false;

	//if (curSkill)
	//{
	//	curSkill->Destroy();
	//	curSkill = nullptr;
	//}
	onAttackEnd.Broadcast();
}

void ACJPlayer::AttackCheck()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);
	bool result = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(attackRadius),
		//FCollisionShape::MakeCapsule(FVector(attackRange, attackRadius/2, attackRadius/2)),
		params
	);

	FCollisionShape::MakeCapsule(FVector());
	FVector traceVec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + traceVec * 0.5f;
	float halfHeight = attackRange * 0.5f + attackRadius;
	FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
	FColor drawColor = result ? FColor::Green : FColor::Red;
	float debugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		center,
		halfHeight,
		attackRadius,
		capsuleRot,
		drawColor,
		false,
		debugLifeTime
	);

	for (FHitResult hitResult : hitResults)
	{
		FDamageEvent damageEvent;
		hitResult.Actor->TakeDamage(playerState->attack, damageEvent, playerController, this);
	}

}

void ACJPlayer::Key1()
{
	playerController->GetShortcutWidget()->UseShortcut(1);
}

void ACJPlayer::Key2()
{
	playerController->GetShortcutWidget()->UseShortcut(2);
}

void ACJPlayer::Key3()
{
	playerController->GetShortcutWidget()->UseShortcut(3);
}

void ACJPlayer::Key4()
{
	playerController->GetShortcutWidget()->UseShortcut(4);
}

void ACJPlayer::Key5()
{
	playerController->GetShortcutWidget()->UseShortcut(5);
}

void ACJPlayer::AddExp(int32 incomeExp)
{
	curExp += incomeExp;

	if (curExp >= nextExp)
	{
		LevelUp();
	}
}

void ACJPlayer::LevelUp()
{
	auto gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	CJCHECK(gameInstance);

	level += 1;
	curExp = 0;

	playerState->maxHP = gameInstance->GetPlayerStatData(level)->maxHP;
	playerState->maxMP = gameInstance->GetPlayerStatData(level)->maxMP;
	attack = playerState->attack = gameInstance->GetPlayerStatData(level)->attack;

	curExp = gameInstance->GetPlayerStatData(level)->curExp;
	nextExp = gameInstance->GetPlayerStatData(level)->nextExp;

	animInstance->PlayLvUpMontage();
	lvUpParticle->Activate(true);
}

float ACJPlayer::TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent,
	class AController* eventInstigator, AActor* damageCauser)
{
	float finalDamage = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	playerState->ApplyDamage(finalDamage);

	return finalDamage;
}

void ACJPlayer::ToggleCursor()
{
	if (playerController) playerController->MouseCursorToggle();
}

void ACJPlayer::TurnOnKeyUI()
{
	if (playerController) playerController->TurnOnCustomWidget();
}

void ACJPlayer::TurnOnSkillWidget()
{
	if (playerController) playerController->TurnOnSkillWidget();
}

void ACJPlayer::JumpEnd()
{
	climbingComponent->JumpEnd();
}

void ACJPlayer::UnGrab()
{
	climbingComponent->UnGrab();
}