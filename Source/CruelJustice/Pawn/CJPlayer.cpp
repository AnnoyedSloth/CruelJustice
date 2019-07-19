// Fill out your copyright notice in the Description page of Project Settings.

#include "CJPlayer.h"
#include "Controller/CJPlayerController.h"
#include "Animation/CJPlayerAnimInstance.h"
#include "ConstructorHelpers.h"

ACJPlayer::ACJPlayer()
{
	// Create Components
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

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

	// Setup hierarchy structure
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	mesh->SetupAttachment(RootComponent);

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

	currentCombo = 0;
}

void ACJPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	playerController = Cast<ACJPlayerController>(GetController());
	animInstance = Cast<UCJPlayerAnimInstance>(mesh->GetAnimInstance());

	animInstance->OnMontageEnded.AddDynamic(this, &ACJPlayer::OnAttackMontageEnded);

	animInstance->onNextAttackCheck.AddLambda([this]() -> void {

		//ABLOG(Warning, TEXT("OnNextAttackCheck"))
		//canNextCombo = false;

		if (isAttacking)
		{
			//ABLOG(Warning, TEXT("currentCombo = %d"), currentCombo);
			AttackStartComboState();
			animInstance->JumpToAttackMontageSection(currentCombo);
			CJLOG(Warning, TEXT("Current Combo num : %d"), currentCombo);
		}
		else
		{
			animInstance->JumpToRecoveryMontageSection(currentCombo);			
		}
	});

}

void ACJPlayer::BeginPlay()
{
	Super::BeginPlay();


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
	

}

void ACJPlayer::MoveForward(float value)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), value);
}

void ACJPlayer::MoveRight(float value)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), value);
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
	animInstance->PlayAttackMontage();
	isAttacking = true;
}

void ACJPlayer::AttackEnd()
{
	isAttacking = false;
	currentCombo = 0;
	
}

void ACJPlayer::AttackStartComboState()
{
	currentCombo = FMath::Clamp<int32>(currentCombo + 1, 1, 4);
}

void ACJPlayer::OnAttackMontageEnded(UAnimMontage* montage, bool isInterrupted)
{
	CJLOG(Warning, TEXT("Attack ended"));
	
	isAttacking = false;

}