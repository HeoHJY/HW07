#include "PawnGameMode.h"
#include "MyPawn.h"

APawnGameMode::APawnGameMode()
{
	DefaultPawnClass = AMyPawn::StaticClass();
}
