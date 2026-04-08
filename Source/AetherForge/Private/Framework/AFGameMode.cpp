
#include "AetherForge/Public/Framework/AFGameMode.h"

#include "Character/AFCharacterBase.h"
#include "Framework/AFGameState.h"
#include "Player/AFPlayerController.h"
#include "Player/AFPlayerState.h"

AAFGameMode::AAFGameMode()
{
	DefaultPawnClass = AAFCharacterBase::StaticClass();
	PlayerControllerClass = AAFPlayerController::StaticClass();
	PlayerStateClass = AAFPlayerState::StaticClass();
	GameStateClass = AAFGameState::StaticClass();
}

