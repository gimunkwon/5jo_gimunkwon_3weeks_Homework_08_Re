#include "UI/Player/PlayerHUDWidget.h"

#include "Components/ProgressBar.h"

void UPlayerHUDWidget::UpdatePlayerHPBar(float MaxHP, float CurrentHP)
{
	if (Progress_HP)
	{
		Progress_HP->SetPercent(CurrentHP / MaxHP);
	}
}
