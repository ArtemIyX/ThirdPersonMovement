/*
Developed by ArtemIyX
GitHub: https://github.com/ArtemIyX/
Credits: 1play2fun123@gmail.com
*/

// ReSharper disable CppUE4ProbableMemoryIssuesWithUObject
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonMovement/TRMLib.h"

#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class THIRDPERSONMOVEMENT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

#pragma region PrivateVars
private:
	EMoveState movingState;
#pragma endregion PrivateVars
#pragma region PrivateMethods
private:
	void MouseXHandle(float value);
	void MouseYHandle(float value);
	void MoveForwardHandle(float value);
	void MoveRightHandle(float value);

	void RunHandlePressed();
	void RunHandleReleased();

	void CrouchHandle();
	
	void SetMovingState(EMoveState value);
#pragma endregion PrivateMethods
#pragma region ProtectedVars
protected:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float WalkSpeed;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float SprintSpeed;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float CrouchSpeed;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float CrouchSprintSpeed;
	
#pragma endregion ProtectedVars
#pragma region ProtectedMethods
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	virtual bool CanStartRunning() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
    virtual bool CanStartRunningCrouched() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
    virtual bool CanStartCrouching() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	virtual bool CanStandUp() const;

	
	void TryStartStandRunning();
	void TryStopStandRunning();
	void TryCrouch();
	void TryUnCrouch();
	void TryStartCrouchRunning();
	void TryStopCrouchRunning();
#pragma endregion ProtectedMethods
#pragma region PublicMethods
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EMoveState GetMovingState() const { return movingState; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetWalkSpeed() const {return WalkSpeed;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE float GetSprintSpeed() const {return SprintSpeed;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE float GetCrouchSpeed() const {return CrouchSpeed;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE float GetCrouchSprintSpeed() const {return CrouchSprintSpeed;}
#pragma endregion PublicMethods
};
