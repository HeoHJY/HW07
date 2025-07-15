#include "PawnController.h"
#include "EnhancedInputSubsystems.h"


APawnController::APawnController()
	:InputMappingContext(nullptr), MoveAction(nullptr),
	LookAction(nullptr)
{

}

void APawnController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}