#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaveNotifyWidget.generated.h"

class UTextBlock;

UCLASS()
class NBC_DOWORK_08_RE_API UWaveNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateWaveInfoText(int32 CurrentWaveIndex);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_WaveInfo;
};
