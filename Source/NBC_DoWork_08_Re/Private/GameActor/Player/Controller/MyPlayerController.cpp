#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = Cast<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()))
		{
			SubSystem->AddMappingContext(IMC_Default,0);
		}
	}
}
