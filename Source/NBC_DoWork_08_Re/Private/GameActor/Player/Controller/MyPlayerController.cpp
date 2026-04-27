#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "UI/Player/PlayerHUDWidget.h"

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
	
	if (Widget_HUD)
	{
		WidgetInst_HUD = CreateWidget<UPlayerHUDWidget>(this, Widget_HUD);
		if (WidgetInst_HUD)
		{
			WidgetInst_HUD->AddToViewport();
		}
	}
}
