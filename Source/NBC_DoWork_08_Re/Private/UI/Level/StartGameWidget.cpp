#include "UI/Level/StartGameWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UStartGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_StartGame)
	{
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartGameWidget::OnStartBtn);
	}
	if (Btn_ExitGame)
	{
		Btn_ExitGame->OnClicked.AddDynamic(this, &UStartGameWidget::OnExitBtn);
	}
}

void UStartGameWidget::OnStartBtn()
{
	UE_LOG(LogTemp,Warning,TEXT("스타트 버튼 눌림"));
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("L_Level1"));
}

void UStartGameWidget::OnExitBtn()
{
	UE_LOG(LogTemp,Warning,TEXT("게임종료 버튼 눌림"));
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit, false);
}
