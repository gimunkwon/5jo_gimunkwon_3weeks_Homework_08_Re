#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class NBC_DOWORK_08_RE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateGameOverText(bool bIsPlayerDead);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_GameOver;
};
