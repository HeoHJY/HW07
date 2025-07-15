#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UCLASS()
class SP1_API AItem : public AActor
{
	GENERATED_BODY()

public:	
	AItem();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Item|Actions")
	void ResetActorPosition();
	UFUNCTION(BlueprintPure, Category="Item|Properties")
	float GetRotationSpeed() const;
	UFUNCTION(BlueprintImplementableEvent, Category="Item|Event")
	void OnItemPickedUp();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Item|Components");
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item|Components");
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Properties");
	float RotationSpeed;
};
