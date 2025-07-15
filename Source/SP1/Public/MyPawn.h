#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UArrowComponent;
struct FInputActionValue;

UCLASS()
class SP1_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Mesh")
	USkeletalMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Collision")
	UBoxComponent* BoxComp;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSens;

private:
	float MoveSpeed;
	float YawValue;
	float PitchValue;
	bool bIsLand;
};
