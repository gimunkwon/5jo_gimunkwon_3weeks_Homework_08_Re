#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

class UGameOverWidget;
class UWaveNotifyWidget;
class UStageNotifyWidget;

UCLASS()
class NBC_DOWORK_08_RE_API AMyGameState : public AGameState
{
	GENERATED_BODY()
public:
	AMyGameState();
	
	void OnDeadZombie();
	void RegisterSpawnVolume(AActor* SpawnVolume);
	void RegisterWaveGate(AActor* WaveGate);
	void GameOver(bool bIsDead);
protected:
	virtual void BeginPlay() override;
	
	void StartStage(int32 StageIndex);
	void EndStage();
	
	void StartWave(int32 WaveIndex);
	void EndWave();
	
	UPROPERTY()
	TArray<AActor*> WaveGateArr;
	UPROPERTY()
	TArray<AActor*> SpawnVolumeArr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Map")
	TArray<FName> LevelNameArr;
	
#pragma region Widget
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> Widget_WaveInfo;
	UPROPERTY()
	TObjectPtr<UWaveNotifyWidget> Widget_WaveInfoInst;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> Widget_StageInfo;
	UPROPERTY()
	TObjectPtr<UStageNotifyWidget> Widget_StageInfoInst;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> Widget_GameOver;
	UPROPERTY()
	TObjectPtr<UGameOverWidget> Widget_GameOverInst;
#pragma endregion
	
private:
	int32 CurrentStageIndex;
	int32 CurrentWaveIndex;
	int32 RemainingStageZombieCount;
	int32 RemainingWaveZombieCount;
	
	FTimerHandle StageWidgetTimerHandle;
	FTimerHandle WaveWidgetTimerHandle;
};
