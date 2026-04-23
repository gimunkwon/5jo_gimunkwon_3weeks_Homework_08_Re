#include "NBC_DoWork_08_Re/Public/Global/MyGameMode.h"

#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"
#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMyPlayer::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
