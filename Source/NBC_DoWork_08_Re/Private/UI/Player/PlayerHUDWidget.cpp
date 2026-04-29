#include "UI/Player/PlayerHUDWidget.h"

#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameActor/Player/MyPlayer.h"

void UPlayerHUDWidget::UpdatePlayerHPBar(float MaxHP, float CurrentHP)
{
	if (Progress_HP)
	{
		Progress_HP->SetPercent(CurrentHP / MaxHP);
	}
}

void UPlayerHUDWidget::UpdateSelectBorder(EPlayerBattleState CurrentState)
{
	if (Border_Bat && Border_Gun)
	{
		switch (CurrentState)
		{
		case EPlayerBattleState::Melee:
			Border_Gun->SetBrushColor(FLinearColor::White);
			Border_Bat->SetBrushColor(FLinearColor::Gray);
			break;
		case EPlayerBattleState::Gun:
			Border_Bat->SetBrushColor(FLinearColor::White);
			Border_Gun->SetBrushColor(FLinearColor::Gray);
			break;
		}
	}
}

void UPlayerHUDWidget::UpdateAmmoText(int32 CurrentAmmo, int32 MaxAmmo)
{
	if (Text_GunAmmo)
	{
		FString AmmoText = FString::Printf(TEXT("%d / %d"),CurrentAmmo,MaxAmmo);
		Text_GunAmmo->SetText(FText::FromString(AmmoText));
	}
}

void UPlayerHUDWidget::UpdateStageAndWaveText(int32 CurrentStage, int32 CurrentWave)
{
	if (Text_StageAWave)
	{
		FString StageAWaveString = FString::Printf(TEXT("Stage : %d | Wave : %d"),CurrentStage,CurrentWave);
		Text_StageAWave->SetText(FText::FromString(StageAWaveString));
	}
}
