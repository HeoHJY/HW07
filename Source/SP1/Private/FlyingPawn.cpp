#include "FlyingPawn.h"
#include "EnhancedInputComponent.h"
#include "PawnController.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AFlyingPawn::AFlyingPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetSimulatePhysics(false);
	RootComponent = BoxComp;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->bIsEditorOnly = false;
	ArrowComp->SetupAttachment(RootComponent);

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

	MoveSpeed = 1200.0f;
	LookSens = 1.5f;
	YawValue = 0.f;
	PitchValue = 0.f;
	GravityValue = -10.f;
	FallValue = 0.f;
	CurrentSpeed = MoveSpeed;
	bIsLand = true;
	bIsGetInput = false;
}

void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsLand = CheckLandGround();

	ApplyGravity(DeltaTime);
}

void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
					&AFlyingPawn::Move
				);
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&AFlyingPawn::EndGetInput
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Look
				);
			}
		}
	}
}

void AFlyingPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector MoveInput = value.Get<FVector>();

	if (!MoveInput.IsNearlyZero())
	{
		CurrentSpeed = bIsLand ? MoveSpeed : (MoveSpeed * 0.7f);

		bIsGetInput = true;

		const FVector MoveDirection = 
			(GetActorForwardVector() * MoveInput.X) + 
			(GetActorRightVector() * MoveInput.Y) +
			(GetActorUpVector() * MoveInput.Z);

		const FVector Offset = MoveDirection * CurrentSpeed * GetWorld()->GetDeltaSeconds();

		AddActorWorldOffset(Offset, true);
	}
}

void AFlyingPawn::Look(const FInputActionValue& value)
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

void AFlyingPawn::ApplyGravity(float DeltaTime)
{
	if (bIsLand)
	{
		FallValue = 0;
	}
	else
	{
		if (!bIsGetInput)
		{
			FallValue += GravityValue * DeltaTime;
		}
		else
		{
			FallValue = GravityValue * 0.2f;
		}
	}

	AddActorWorldOffset(FVector(0.f, 0.f, FallValue), true);
}

bool AFlyingPawn::CheckLandGround()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, 150.f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(
		HitResult, Start, End, ECC_Visibility, Params);
}