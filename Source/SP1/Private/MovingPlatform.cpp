#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneComp);

	MoveSpeed = 100.0f;
	MaxRange = 500.0f;
	Velocity = { 0, 1, 0 };
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	NewLocation = StartLocation;

	GetWorld()->GetTimerManager().SetTimer
	(
		MoveTimerHandle, this, &AMovingPlatform::MoveActorLocation, 0.2f, true
	);

	GetWorld()->GetTimerManager().SetTimer
	(
		VisibleTimerHandle, this, &AMovingPlatform::ActorChangeVisible, 2.0f, true
	);
}

void AMovingPlatform::MoveActorLocation()
{
	const float MoveDeltaTime = 0.2f;

	if (FVector::Dist(StartLocation, NewLocation) > MaxRange)
	{
		Velocity = -Velocity;
	}

	NewLocation = NewLocation + (Velocity * MoveSpeed * MoveDeltaTime);

	SetActorLocation(NewLocation);
}

void AMovingPlatform::ActorChangeVisible()
{
	if (bActorInvisible)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		bActorInvisible = false;
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		bActorInvisible = true;
	}
}

