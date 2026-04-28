#include "Global/MyGameState.h"

#include "Global/SpawnSystem/SpawnVolume.h"

AMyGameState::AMyGameState()
{
	CurrentWaveIndex = 1;
	CurrentStageIndex = 1;
	RemainingStageZombieCount = 0;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameState::StartStage(int32 StageIndex)
{
	ASpawnVolume* SpawnVolumes = nullptr;
	for (AActor* SpawnCount : SpawnVolumeArr)
	{
		SpawnVolumes = Cast<ASpawnVolume>(SpawnCount);
		if (SpawnVolumes)
		{
			RemainingStageZombieCount += SpawnVolumes->GetSpawnCount(SpawnVolumes->GetSpawnIndex());
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("전체 스테이지 좀비 수 %d"),RemainingStageZombieCount);
	
	if (CurrentWaveIndex == 1)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(SpawnVolumeArr[0]);
		StartWave(CurrentWaveIndex,SpawnVolume->GetSpawnCount(CurrentWaveIndex));
	}
}

void AMyGameState::EndStage()
{
	UE_LOG(LogTemp,Warning,TEXT("레벨 %d 종료"), CurrentStageIndex);
	StartStage(CurrentStageIndex++);
}

void AMyGameState::StartWave(int32 WaveIndex,int32 WaveZombieCount)
{
	RemainingWaveZombieCount = WaveZombieCount;
	UE_LOG(LogTemp,Warning,TEXT("%d 웨이브 시작!! 현재 웨이브 좀비 수: %d"),WaveIndex,RemainingWaveZombieCount);
}

void AMyGameState::EndWave()
{
	UE_LOG(LogTemp,Warning,TEXT("Wave : [%d] 종료"),CurrentWaveIndex);
	CurrentWaveIndex++;
}

void AMyGameState::OnDeadZombie()
{
	RemainingWaveZombieCount--;
	if (RemainingWaveZombieCount == 0)
	{
		EndWave();
	}
}

void AMyGameState::RegisterSpawnVolume(AActor* SpawnVolume)
{
	SpawnVolumeArr.Add(SpawnVolume);
	
	if (SpawnVolumeArr.Num() == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (ASpawnVolume* SpawnVolumes = Cast<ASpawnVolume>(SpawnVolumeArr[i]))
			{
				UE_LOG(LogTemp,Warning,TEXT("Register Spawn Volume %s,SpawnZombieNumber : %d"),*SpawnVolumes->GetName(),SpawnVolumes->GetSpawnCount(SpawnVolumes->GetSpawnIndex()));
			}
		}
		StartStage(CurrentStageIndex);
	}
}
