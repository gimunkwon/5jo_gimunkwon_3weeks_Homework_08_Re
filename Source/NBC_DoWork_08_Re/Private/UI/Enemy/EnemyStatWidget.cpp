#include "UI/Enemy/EnemyStatWidget.h"

#include "Components/ProgressBar.h"

void UEnemyStatWidget::UpdateHPProgressBar(float CurrentHP, float MaxHP)
{
	if (Progress_HP)
	{
		Progress_HP->SetPercent(CurrentHP / MaxHP);
	}
}
