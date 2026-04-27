#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class NBC_DOWORK_08_RE_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdatePlayerHPBar(float MaxHP, float CurrentHP);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Progress_HP;
};
