#include "RotationActor.h"

ARotationActor::ARotationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneComp);

	RotationSpeedX = 100.0f; RotationSpeedY = 100.0f; RotationSpeedZ = 100.0f;
}

void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(RotationSpeedX * DeltaTime, RotationSpeedY * DeltaTime, RotationSpeedZ * DeltaTime));
}

