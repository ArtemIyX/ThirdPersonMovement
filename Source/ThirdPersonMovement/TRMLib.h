/*
Developed by ArtemIyX
GitHub: https://github.com/ArtemIyX/
Credits: 1play2fun123@gmail.com
*/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TRMLib.generated.h"

UENUM(Blueprintable,BlueprintType)
enum EMoveState
{
	Walking,
	Running,
	Crouching,
	CrouchRunning
};



UCLASS()
class THIRDPERSONMOVEMENT_API UTRMLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static FString EMoveStateToString(EMoveState value);
};
