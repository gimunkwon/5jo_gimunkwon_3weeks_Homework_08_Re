#include "Global/MyGameState.h"

#include "Blueprint/UserWidget.h"
#include "Global/MyGameInstance.h"
#include "Global/SpawnSystem/SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Object/GateToNextWave.h"
#include "UI/Level/GameOverWidget.h"
#include "UI/Level/StageNotifyWidget.h"
#include "UI/Level/WaveNotifyWidget.h"

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
		UE_LOG(LogTemp,Warning,TEXT("GameState CurrentStateIndex : %d | GameInst StageIndex : %d"),CurrentStageIndex,GI->CurrentStageIndex);
	}
}

void AMyGameState::StartStage(int32 StageIndex)
{
	UMyGameInstance* GI = nullptr;
	GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		if(GI->CurrentStageIndex > 3)
		{
			GameOver(false);
		}
	}
	
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
	
	if (Widget_StageInfo)
	{
		if (!Widget_StageInfoInst) Widget_StageInfoInst = CreateWidget<UStageNotifyWidget>(GetWorld()->GetFirstPlayerController(),Widget_StageInfo);
		
		if (Widget_StageInfoInst)
		{
			Widget_StageInfoInst->AddToViewport();
			Widget_StageInfoInst->UpdateStageInfoText(GI->CurrentStageIndex);
			
			GetWorldTimerManager().SetTimer(StageWidgetTimerHandle,[this]()
			{
				Widget_StageInfoInst->RemoveFromParent();
				StartWave(CurrentWaveIndex);
			},2.f,false);
		}
	}
}

void AMyGameState::EndStage()
{
	UE_LOG(LogTemp,Warning,TEXT("레벨 %d 종료"), CurrentStageIndex);
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))
	{
		GI->CurrentStageIndex++;
		
		if (GI->CurrentStageIndex > 3)
		{
			UE_LOG(LogTemp,Warning,TEXT("게임 클리어!!"))
			return;
		}
	}

	UGameplayStatics::OpenLevel(GetWorld(),LevelNameArr[++CurrentStageIndex - 1]);
}

void AMyGameState::StartWave(int32 WaveIndex)
{
	if (Widget_WaveInfo)
	{
		Widget_WaveInfoInst = CreateWidget<UWaveNotifyWidget>(GetWorld()->GetFirstPlayerController(),Widget_WaveInfo);
		if (Widget_WaveInfoInst)
		{
			Widget_WaveInfoInst->AddToViewport();
			Widget_WaveInfoInst->UpdateWaveInfoText(CurrentWaveIndex);
			
			GetWorldTimerManager().SetTimer(WaveWidgetTimerHandle,[this]()
			{
				Widget_WaveInfoInst->RemoveFromParent();
			},2.f,false);
		}
	}
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

void AMyGameState::GameOver(bool bIsDead)
{
	if (Widget_GameOver)
	{
		Widget_GameOverInst = CreateWidget<UGameOverWidget>(GetWorld()->GetFirstPlayerController(),Widget_GameOver);
		if (Widget_GameOverInst)
		{
			Widget_GameOverInst->AddToViewport();
			//TODO:: 플레이어가 죽었는지 정상적으로 클리어가 됬는지에 따른 GameOverWidget Text값 조정
			if (!bIsDead)
			{
				UE_LOG(LogTemp,Warning,TEXT("게임 클리어!!"));
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("게임 오버..."));
			}
		}
	}
	
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
