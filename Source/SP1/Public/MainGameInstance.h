#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"


UCLASS()
class SP1_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMainGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
