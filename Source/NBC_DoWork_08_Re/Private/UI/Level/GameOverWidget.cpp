#include "UI/Level/GameOverWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Global/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_ReturnStart)
	{
		Btn_ReturnStart->OnClicked.AddDynamic(this, &UGameOverWidget::OnReturnStartClicked);
	}
	if (Btn_Exit)
	{
		Btn_Exit->OnClicked.AddDynamic(this, &UGameOverWidget::OnExitClicked);
	}
}

void UGameOverWidget::UpdateGameOverText(bool bIsPlayerDead)
{
	if (Text_GameOver)
	{
		FString GameOverText = "";
		if (bIsPlayerDead)
		{
			GameOverText = FString::Printf(TEXT("게임 오버"));
			Text_GameOver->SetText(FText::FromString(GameOverText));
		}
		else
		{
			GameOverText = FString::Printf(TEXT("게임 클리어"));
			Text_GameOver->SetText(FText::FromString(GameOverText));
		}
	}
}

void UGameOverWidget::OnReturnStartClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("L_StatrLevel"));
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->InitializeGameInstanceValue();
	}
}

void UGameOverWidget::OnExitClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("게임종료"));
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit, false);
	
}
