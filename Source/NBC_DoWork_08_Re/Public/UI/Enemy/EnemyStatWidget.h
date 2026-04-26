#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStatWidget.generated.h"

class UProgressBar;

UCLASS()
class NBC_DOWORK_08_RE_API UEnemyStatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHPProgressBar(float CurrentHP, float MaxHP);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Progress_HP;
};
