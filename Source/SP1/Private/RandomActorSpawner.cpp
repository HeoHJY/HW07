#include "RandomActorSpawner.h"

ARandomActorSpawner::ARandomActorSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpawnCount = 10;
	CurrentLocation = GetActorLocation();
	RandomLocation = CurrentLocation;
	MaxVector = 500;
	MinVector = -500;
}

void ARandomActorSpawner::BeginPlay()  
{  
    Super::BeginPlay();  
    
    for (int i = 0; i < SpawnCount; i++)  
    {  
        RandomLocation.X = CurrentLocation.X + FMath::FRandRange(static_cast<float>(MinVector), static_cast<float>(MaxVector));  
        RandomLocation.Y = CurrentLocation.Y + FMath::FRandRange(static_cast<float>(MinVector), static_cast<float>(MaxVector));  

        if (Actor)  
        {  
            GetWorld()->SpawnActor<AActor>(Actor, RandomLocation, FRotator::ZeroRotator);  
        }  
    }

    Destroy();
}


