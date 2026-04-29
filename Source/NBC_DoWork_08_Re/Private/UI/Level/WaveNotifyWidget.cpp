#include "UI/Level/WaveNotifyWidget.h"

#include "Components/TextBlock.h"

void UWaveNotifyWidget::UpdateWaveInfoText(int32 CurrentWaveIndex)
{
	if (Text_WaveInfo)
	{
		FString WaveText = FString::Printf(TEXT("%d Wave Start!!"),CurrentWaveIndex);
		Text_WaveInfo->SetText(FText::FromString(WaveText));
	}
}
