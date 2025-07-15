#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomActorSpawner.generated.h"

UCLASS()
class SP1_API ARandomActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomActorSpawner();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	int SpawnCount;
	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	int MaxVector;
	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	int MinVector;

	FVector CurrentLocation;
	FVector RandomLocation;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<AActor> Actor;
};
