#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Global/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Level/StartGameWidget.h"
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
	
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
	{
		if (!GI->bIsStarted)
		{
			GI->bIsStarted = true;
			if (Widget_StartLevel)
			{
				Widget_StartLevelInst = CreateWidget<UStartGameWidget>(this,Widget_StartLevel);
				if (Widget_StartLevelInst)
				{
					Widget_StartLevelInst->AddToViewport();
					SetInputMode(FInputModeUIOnly());
					DisableInput(this);
				}
			}
		}
		else
		{
			if (Widget_HUD)
			{
				WidgetInst_HUD = CreateWidget<UPlayerHUDWidget>(this, Widget_HUD);
				if (WidgetInst_HUD)
				{
					WidgetInst_HUD->AddToViewport();
					
					FInputModeGameAndUI InputMode;
					InputMode.SetWidgetToFocus(WidgetInst_HUD->TakeWidget());
					InputMode.SetHideCursorDuringCapture(false);
					SetInputMode(InputMode);
					EnableInput(this);
				}
			}
		}
	}
	
	
	
}
