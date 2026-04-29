#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class NBC_DOWORK_08_RE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateGameOverText(bool bIsPlayerDead);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_GameOver;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_ReturnStart;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Exit;
	
	UFUNCTION()
	void OnReturnStartClicked();
	UFUNCTION()
	void OnExitClicked();
};
