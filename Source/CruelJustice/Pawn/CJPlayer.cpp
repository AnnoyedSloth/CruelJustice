// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayer.h"
#include "Controller/CJPlayerController.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "Skill/CJSkill.h"
#include "Skill/CJPlayerSkill1_Slash.h"
#include "Skill/CJPlayerSkill2_Fireball.h"
#include "CJPlayerState.h"
#include "CJGameInstance.h"
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
	
	//static ConstructorHelpers::FClassFinder<ACJSkill>
	//	SKILL1(TEXT("/Script/CruelJustice.CJPlayerSkill1_Slash"));
	//if (SKILL1.Succeeded())
	//{
	//	CJLOG(Warning, TEXT("Skill1 found"));
	//	skills.Add(Cast<ACJPlayerSkill1_Slash>(SKILL1.Class));
	//}
	//else
	//{
	//	CJLOG(Warning, TEXT("Skill1 not found"));
	//}

	//static ConstructorHelpers::FClassFinder<ACJSkill>
	//	SKILL2(TEXT("/Script/CruelJustice.CJPlayerSkill2_Fireball"));
	//if (SKILL2.Succeeded())
	//{
	//	CJLOG(Warning, TEXT("Skill2 found"));
	//	ACJPlayerSkill2_Fireball* fireball = Cast<ACJPlayerSkill2_Fireball>(*SKILL2.Class);
	//	if (fireball)
	//	{
	//		CJLOG(Warning, TEXT("Skill2 found and Casting succeeded"));
	//	}
	//	else
	//	{
	//		CJLOG(Warning, TEXT("Skill2 found and Casting failed"));
	//	}
	//	//skills.Add(Cast<ACJPlayerSkill2_Fireball>(SKILL2.Class));
	//}
	//else
	//{
	//	CJLOG(Warning, TEXT("Skill2 not found"));
	//}




	//skills.Add(Cast<ACJPlayerSkill1_Slash>(ACJPlayerSkill1_Slash::StaticClass()));
	//skills.Add(Cast<ACJPlayerSkill2_Fireball>(ACJPlayerSkill2_Fireball::StaticClass()));


	// Setup hierarchy structure
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	mesh->SetupAttachment(RootComponent);
	lvUpParticle->SetupAttachment(RootComponent);

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
	
	playerController = Cast<ACJPlayerController>(GetController());
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

	playerState = Cast<ACJPlayerState>(PlayerState);
	CJCHECK(playerState);

	// Setup Initial level when start game
	auto gameInstance = Cast<UCJGameInstance>(GetGameInstance());
	CJCHECK(gameInstance);

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

	playerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	playerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ACJPlayer::Attack);
	playerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ACJPlayer::AttackEnd);
	playerInputComponent->BindAction(TEXT("Roll"), IE_Pressed, this, &ACJPlayer::Dodge);

	playerInputComponent->BindAction(TEXT("Skill1_Slash"), IE_Pressed, this, &ACJPlayer::Skill1);
	playerInputComponent->BindAction(TEXT("Skill2_Fireball"), IE_Pressed, this, &ACJPlayer::Skill2);


}

void ACJPlayer::MoveForward(float value)
{
	if(!isAttacking) AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), value);
}

void ACJPlayer::MoveRight(float value)
{
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

	for (FHitResult result : hitResults)
	{
		FDamageEvent damageEvent;
		result.Actor->TakeDamage(playerState->attack, damageEvent, playerController, this);
	}

}

void ACJPlayer::Skill1()
{
	if (isAttacking) return;
	isAttacking = true;
	curSkill = GetWorld()->SpawnActor<ACJPlayerSkill1_Slash>(this->GetActorLocation(), this->GetActorRotation());
	curSkill->InitSkill(this);
	curSkill->PlaySkill();
	
}

void ACJPlayer::Skill2()
{
	if (isAttacking) return;
	isAttacking = true;
	curSkill = GetWorld()->SpawnActor<ACJPlayerSkill2_Fireball>(this->GetActorLocation(), this->GetActorRotation());
	curSkill->InitSkill(this);
	curSkill->PlaySkill();
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

	playerState->ApplyDamage(damageAmount);

	return finalDamage;
}