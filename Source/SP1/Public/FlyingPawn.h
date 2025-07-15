#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingPawn.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UArrowComponent;
struct FInputActionValue;

UCLASS()
class SP1_API AFlyingPawn : public APawn
{
	GENERATED_BODY()

public:
	AFlyingPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Mesh")
	USkeletalMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Arrow")
	UArrowComponent* ArrowComp;
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
	
	void ApplyGravity(float DeltaTime);
	void EndGetInput() { bIsGetInput = false; }
	bool CheckLandGround();
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSens;


private:
	float MoveSpeed;
	float CurrentSpeed;
	float YawValue;
	float PitchValue;
	float GravityValue;
	float FallValue;
	bool bIsLand;
	bool bIsGetInput;
};
