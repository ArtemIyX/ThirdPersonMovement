#include "ThirdPersonMovement/Gameplay/Main/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = UObject::CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	Camera = UObject::CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	WalkSpeed = 300.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	SprintSpeed = 600.0f;
	CrouchSpeed = 150.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	CrouchSprintSpeed = 350.0f;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool ABaseCharacter::CanStartRunning() const
{
	return !GetMovementComponent()->IsCrouching()
		&& GetMovingState() == EMoveState::Walking;
}

bool ABaseCharacter::CanStartRunningCrouched() const
{
	return GetMovementComponent()->IsCrouching()
		&& GetMovingState() == EMoveState::Crouching;
}

bool ABaseCharacter::CanStartCrouching() const
{
	return !GetMovementComponent()->IsCrouching()
		&& GetMovingState() == EMoveState::Walking;
}

bool ABaseCharacter::CanStandUp() const
{
	return GetMovementComponent()->IsCrouching()
		&& GetMovingState() == EMoveState::Crouching;
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseCharacter::MouseXHandle);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseCharacter::MouseYHandle);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForwardHandle);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRightHandle);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ABaseCharacter::RunHandlePressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ABaseCharacter::RunHandleReleased);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ABaseCharacter::CrouchHandle);
}

void ABaseCharacter::MouseXHandle(float value)
{
	AddControllerYawInput(value);
}

void ABaseCharacter::MouseYHandle(float value)
{
	AddControllerPitchInput(value);
}

void ABaseCharacter::MoveForwardHandle(float value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector
	                 (FRotator(0,
	                           GetControlRotation().Yaw,
	                           0)), value);
}

void ABaseCharacter::MoveRightHandle(float value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector
	                 (FRotator(0,
	                           GetControlRotation().Yaw,
	                           0)), value);
}

void ABaseCharacter::RunHandlePressed()
{
	if (GetMovingState() == EMoveState::Walking)
	{
		if (CanStartRunning())
		{
			TryStartStandRunning();
		}
	}
	else if (GetMovingState() == EMoveState::Crouching)
	{
		if (CanStartRunningCrouched())
		{
			TryStartCrouchRunning();
		}
	}
}

void ABaseCharacter::RunHandleReleased()
{
	if (GetMovingState() == EMoveState::Running)
	{
		TryStopStandRunning();
	}
	else if(GetMovingState() == EMoveState::CrouchRunning)
	{
		TryStopCrouchRunning();
	}
}

void ABaseCharacter::CrouchHandle()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		if (CanStandUp())
		{
			TryUnCrouch();
		}
	}
	else if (GetMovingState() == EMoveState::Walking)
	{
		if (CanCrouch())
		{
			TryCrouch();
		}
	}
}

void ABaseCharacter::TryStartStandRunning()
{
	SetMovingState(EMoveState::Running);
}

void ABaseCharacter::TryStopStandRunning()
{
	SetMovingState(EMoveState::Walking);
}

void ABaseCharacter::TryCrouch()
{
	ACharacter::Crouch();
	SetMovingState(EMoveState::Crouching);
}

void ABaseCharacter::TryUnCrouch()
{
	ACharacter::UnCrouch();
	SetMovingState(EMoveState::Walking);
}

void ABaseCharacter::TryStartCrouchRunning()
{
	SetMovingState(EMoveState::CrouchRunning);
}

void ABaseCharacter::TryStopCrouchRunning()
{
	SetMovingState(EMoveState::Crouching);
}

void ABaseCharacter::SetMovingState(EMoveState value)
{
	movingState = value;
	switch (movingState)
	{
	case Walking:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case Running:
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		break;
	case Crouching:
		GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
		break;
	case CrouchRunning:
		GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSprintSpeed;
		break;
	default: break;
	}
}
