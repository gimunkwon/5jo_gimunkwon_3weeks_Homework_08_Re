#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;
enum class EPlayerBattleState : uint8;
class UBorder;
class UProgressBar;

UCLASS()
class NBC_DOWORK_08_RE_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void UpdatePlayerHPBar(float MaxHP, float CurrentHP);
	void UpdateSelectBorder(EPlayerBattleState CurrentState);
	void UpdateAmmoText(int32 CurrentAmmo, int32 MaxAmmo);
	UFUNCTION()
	void UdpateRemainStageZombieCountText(int32 RemainZombieCount);
	UFUNCTION()
	void UdpateRemainWaveZombieCountText(int32 RemainZombieCount);
	UFUNCTION()
	void UpdateStageAndWaveText(int32 CurrentStage, int32 CurrentWave);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Progress_HP;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> Border_Bat;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> Border_Gun;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_GunAmmo;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_StageAWave;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_RemainStageZombieCount;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_RemainWaveZombieCount;
};
