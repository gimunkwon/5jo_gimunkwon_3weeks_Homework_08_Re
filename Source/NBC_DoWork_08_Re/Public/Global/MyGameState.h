#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AMyGameState : public AGameState
{
	GENERATED_BODY()
public:
	AMyGameState();
	
	void OnDeadZombie();
	void RegisterSpawnVolume(AActor* SpawnVolume);
protected:
	virtual void BeginPlay() override;
	
	void StartStage(int32 StageIndex);
	void EndStage();
	
	void StartWave(int32 WaveIndex,int32 WaveZombieCount);
	void EndWave();
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Object")
	TArray<TSubclassOf<AActor>> WaveGateArr;
	UPROPERTY()
	TArray<AActor*> SpawnVolumeArr;
	
private:
	int32 CurrentStageIndex;
	int32 CurrentWaveIndex;
	int32 RemainingStageZombieCount;
	int32 RemainingWaveZombieCount;
};
