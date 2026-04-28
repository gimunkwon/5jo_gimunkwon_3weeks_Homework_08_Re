#include "Global/MyGameState.h"

#include "Global/MyGameInstance.h"
#include "Global/SpawnSystem/SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Object/GateToNextWave.h"

AMyGameState::AMyGameState()
{
	CurrentWaveIndex = 1;
	CurrentStageIndex = 1;
	RemainingStageZombieCount = 0;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))
	{
		CurrentStageIndex = GI->CurrentStageIndex;
	}
}

void AMyGameState::StartStage(int32 StageIndex)
{
	for (AActor* SpawnCount : SpawnVolumeArr)
	{
		if (ASpawnVolume* SpawnVolumes = Cast<ASpawnVolume>(SpawnCount))
		{
			RemainingStageZombieCount += SpawnVolumes->GetSpawnCount(SpawnVolumes->GetSpawnIndex());
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("전체 스테이지 좀비 수 %d"),RemainingStageZombieCount);
	
	ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(SpawnVolumeArr[CurrentWaveIndex - 1]);
	RemainingWaveZombieCount = SpawnVolume->GetSpawnCount(CurrentWaveIndex);
	StartWave(CurrentWaveIndex);
}

void AMyGameState::EndStage()
{
	UE_LOG(LogTemp,Warning,TEXT("레벨 %d 종료"), CurrentStageIndex);
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))
	{
		GI->CurrentStageIndex++;
	}
	UGameplayStatics::OpenLevel(GetWorld(),LevelNameArr[++CurrentStageIndex - 1]);
}

void AMyGameState::StartWave(int32 WaveIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("%d 웨이브 시작!! 현재 웨이브 좀비 수: %d"),WaveIndex,RemainingWaveZombieCount);
}

void AMyGameState::EndWave()
{
	UE_LOG(LogTemp,Warning,TEXT("Wave : [%d] 종료"),CurrentWaveIndex);
	if (!WaveGateArr.IsEmpty())
	{
		WaveGateArr[0]->Destroy();
		WaveGateArr.RemoveAt(0);
	}
	CurrentWaveIndex++;
	ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(SpawnVolumeArr[CurrentWaveIndex - 1]);
	RemainingWaveZombieCount = SpawnVolume->GetSpawnCount(CurrentWaveIndex);
	StartWave(CurrentWaveIndex);
}

void AMyGameState::OnDeadZombie()
{
	RemainingWaveZombieCount--;
	RemainingStageZombieCount--;
	if (RemainingWaveZombieCount == 0 && RemainingStageZombieCount != 0)
	{
		EndWave();
	}
	if (RemainingStageZombieCount == 0)
	{
		EndStage();
	}
}

void AMyGameState::RegisterSpawnVolume(AActor* SpawnVolume)
{
	SpawnVolumeArr.Add(SpawnVolume);
	
	if (SpawnVolumeArr.Num() == 3)
	{
		for (int i = 0; i < SpawnVolumeArr.Num(); ++i)
		{
			if (ASpawnVolume* SpawnVolumes = Cast<ASpawnVolume>(SpawnVolumeArr[i]))
			{
				UE_LOG(LogTemp,Warning,TEXT("Register Spawn Volume %s,SpawnZombieNumber : %d"),*SpawnVolumes->GetName(),SpawnVolumes->GetSpawnCount(SpawnVolumes->GetSpawnIndex()));
			}
		}
		StartStage(CurrentStageIndex);
	}
}

void AMyGameState::RegisterWaveGate(AActor* WaveGate)
{
	WaveGateArr.Add(WaveGate);
	
	if (WaveGateArr.Num() == 2)
	{
		for (int i = 0; i < WaveGateArr.Num(); ++i)
		{
			if (AGateToNextWave* NextGate = Cast<AGateToNextWave>(WaveGateArr[i]))
			{
				UE_LOG(LogTemp,Warning,TEXT("Register WaveGate %s"),*NextGate->GetName());
			}
		}
	}
}
