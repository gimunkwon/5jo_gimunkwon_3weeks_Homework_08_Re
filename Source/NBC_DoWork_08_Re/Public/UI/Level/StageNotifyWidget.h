#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageNotifyWidget.generated.h"

class UTextBlock;

UCLASS()
class NBC_DOWORK_08_RE_API UStageNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateStageInfoText(int32 CurrentStageIndex);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_StageInfo;
};
