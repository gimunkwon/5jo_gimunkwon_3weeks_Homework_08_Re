#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UStartGameWidget;
class UPlayerHUDWidget;
class UInputAction;
class UInputMappingContext;

UCLASS()
class NBC_DOWORK_08_RE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_SelectBattleMode;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_Attack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_Reload;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_Rotate;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> Widget_HUD;
	UPROPERTY()
	TObjectPtr<UPlayerHUDWidget> WidgetInst_HUD;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> Widget_StartLevel;
	UPROPERTY()
	TObjectPtr<UStartGameWidget> Widget_StartLevelInst;

	
protected:
	virtual void BeginPlay() override;
private:
	bool bIsStarted;
};
