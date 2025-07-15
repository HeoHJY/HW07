#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationActor.generated.h"


UCLASS()
class SP1_API ARotationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotationActor();


protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeedZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Settings")
	USceneComponent* SceneComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	UStaticMeshComponent* StaticMeshComp;
};
