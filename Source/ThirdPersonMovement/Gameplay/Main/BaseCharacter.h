/*
Developed by ArtemIyX
GitHub: https://github.com/ArtemIyX/
Credits: 1play2fun123@gmail.com
*/

// ReSharper disable CppUE4ProbableMemoryIssuesWithUObject
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

#pragma endregion PrivateVars
#pragma region PrivateMethods
private:
	void MouseXHandle(float value);
	void MouseYHandle(float value);
	void MoveForwardHandle(float value);
	void MoveRightHandle(float value);
#pragma endregion PrivateMethods
#pragma region ProtectedVars
protected:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UCameraComponent* Camera;
#pragma endregion ProtectedVars
#pragma region ProtectedMethods
protected:
	virtual void BeginPlay() override;

#pragma endregion ProtectedMethods
#pragma region PublicMethods
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
#pragma endregion PublicMethods
};
