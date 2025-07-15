#include "MainGameMode.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "MainGameState.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	GameStateClass = AMainGameState::StaticClass();
}

