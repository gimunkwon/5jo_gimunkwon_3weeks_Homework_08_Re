#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameWidget.generated.h"

class UButton;

UCLASS()
class NBC_DOWORK_08_RE_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnStartBtn();
	UFUNCTION()
	void OnExitBtn();
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_StartGame;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_ExitGame;
};
