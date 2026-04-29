#include "UI/Level/GameOverWidget.h"

#include "Components/TextBlock.h"

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
