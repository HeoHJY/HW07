#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class SP1_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxRange;
	FVector StartLocation;
	FVector NewLocation;
	bool bActorInvisible;
	void MoveActorLocation();
	void ActorChangeVisible();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector Velocity;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Settings")
	USceneComponent* SceneComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	UStaticMeshComponent* StaticMeshComp;

	FTimerHandle MoveTimerHandle;
	FTimerHandle VisibleTimerHandle;
};
