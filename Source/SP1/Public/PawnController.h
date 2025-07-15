#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SP1_API APawnController : public APlayerController
{
	GENERATED_BODY()

public:
	APawnController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

protected:
	virtual void BeginPlay() override;
};
