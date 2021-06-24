#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = UObject::CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	Camera = UObject::CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		          0)),value);
}

void ABaseCharacter::MoveRightHandle(float value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector
		(FRotator(0,
		          GetControlRotation().Yaw,
		          0)), value);
}
