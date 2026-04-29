#include "UI/Level/StageNotifyWidget.h"

#include "Components/TextBlock.h"

void UStageNotifyWidget::UpdateStageInfoText(int32 CurrentStageIndex)
{
	if (Text_StageInfo)
	{
		FString StageText = FString::Printf(TEXT("%d Stage Enter..."),CurrentStageIndex);
		Text_StageInfo->SetText(FText::FromString(StageText));
	}
}
