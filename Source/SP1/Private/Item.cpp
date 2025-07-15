#include "Item.h"


AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = false;
	RotationSpeed = 300.0f;
}



void AItem::BeginPlay()
{
	Super::BeginPlay();

	OnItemPickedUp();
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}