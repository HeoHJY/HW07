#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "PawnController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"



AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetSimulatePhysics(false);
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MoveSpeed = 800.0f;
	LookSens = 1.5f;
	YawValue = 0.f;
	PitchValue = 0.f;
	bIsLand = true;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawnController* PlayerController = Cast<APawnController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Look
				);
			}
		}
	}
}

void AMyPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!MoveInput.IsNearlyZero())
	{
		const FVector MoveDirection = (GetActorForwardVector() * MoveInput.X) + (GetActorRightVector() * MoveInput.Y);

		const FVector Offset = MoveDirection * MoveSpeed * GetWorld()->GetDeltaSeconds();

		AddActorWorldOffset(Offset, true);
	}
}

void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	if (!LookInput.IsNearlyZero())
	{
		YawValue += LookInput.X * LookSens;
		PitchValue += LookInput.Y * LookSens;

		PitchValue = FMath::Clamp(PitchValue, -40.f, 40.f);

		Controller->SetControlRotation(FRotator(PitchValue, YawValue, 0.f));
	}
}