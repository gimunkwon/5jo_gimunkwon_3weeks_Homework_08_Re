#include "Global/SpawnSystem/SpawnVolume.h"

#include "Components/BoxComponent.h"
#include "DataTable/Level/DT_SpawnZombie.h"
#include "Global/MyGameState.h"


ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComp->SetupAttachment(SceneComp);
	BoxCollisionComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeSpawnPool(WaveIndexValue);
	SpawnZombieInVolume(WaveIndexValue);
	if (AMyGameState* GS = Cast<AMyGameState>(GetWorld()->GetGameState()))
	{
		GS->RegisterSpawnVolume(this);
	}
}

void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnVolume::RandomSpawnPoint()
{
	FVector BoxExtent = BoxCollisionComp->GetScaledBoxExtent();
	FVector Center = BoxCollisionComp->GetComponentLocation();
	
	float RandomX = FMath::FRandRange(BoxExtent.X, -BoxExtent.X);
	float RandomY = FMath::FRandRange(BoxExtent.Y, -BoxExtent.Y);
	
	FVector RandomLocation = Center + FVector(RandomX,RandomY,0.f);
	
	return RandomLocation;
}

void ASpawnVolume::InitializeSpawnPool(int32 WaveIndex)
{
	if (!DT_SpawnValue) return;
	
	const static FString ContextStiring = "InitialSpawnPool";
	FSpawnZombie* WaveData = DT_SpawnValue->FindRow<FSpawnZombie>(TEXT("Level1"),ContextStiring);
	if (WaveData)
	{
		switch (WaveIndex)
		{
		case 1:
			CreatePool(WaveData->Wave1_SpawnCount, Wave1_Pool);
			break;
		case 2:
			CreatePool(WaveData->Wave2_SpawnCount, Wave2_Pool);
			break;
		case 3:
			CreatePool(WaveData->Wave3_SpawnCount, Wave3_Pool);
			break;
		}
	}
}

void ASpawnVolume::CreatePool(const TMap<EZombieType, int32>& SpawnCountMap, TArray<AActor*>& SpawnPool)
{
	for (const auto& Pair : SpawnCountMap)
	{
		EZombieType Type = Pair.Key;
		int32 SpawnCount = Pair.Value;
		
		TSubclassOf<AActor> SelectedClass = nullptr;
		switch (Type)
		{
		case EZombieType::Normal:
			if (ZombieActor.IsValidIndex(0)) SelectedClass = ZombieActor[0];
			break;
		case EZombieType::Running:
			if (ZombieActor.IsValidIndex(1)) SelectedClass = ZombieActor[1];
			break;
		case EZombieType::Boss:
			if (ZombieActor.IsValidIndex(2)) SelectedClass = ZombieActor[2];
			break;
		}
		
		if (!SelectedClass) continue;
		
		for(int32 i = 0; i < SpawnCount; i++)
		{
			AActor* NewZombie = GetWorld()->SpawnActor<AActor>(SelectedClass,RandomSpawnPoint(),FRotator::ZeroRotator);
			if (NewZombie)
			{
				NewZombie->SetActorHiddenInGame(true);
				NewZombie->SetActorEnableCollision(false);
				NewZombie->SetActorTickEnabled(false);
				
				SpawnPool.Add(NewZombie);
			}
		}
	}
}

void ASpawnVolume::SpawnZombieInVolume(int32 WaveIndex)
{
	TArray<AActor*>* TargetPool = nullptr;

	switch (WaveIndex)
	{
	case 1:
		TargetPool = &Wave1_Pool;
		break;
	case 2:
		TargetPool = &Wave2_Pool;
		break;
	case 3:
		TargetPool = &Wave3_Pool;
		break;
	}
	
	if (TargetPool)
	{
		for (AActor* Zombie : *TargetPool)
		{
			if (Zombie)
			{
				Zombie->SetActorHiddenInGame(false);
				Zombie->SetActorEnableCollision(true);
				Zombie->SetActorTickEnabled(true);
			}
		}
	}
}

int32 ASpawnVolume::GetSpawnCount(int32 WaveIndex)
{
	int32 SpawnCount = 0;
	switch (WaveIndex)
	{
	case 1:
		SpawnCount = Wave1_Pool.Num();
		break;
	case 2:
		SpawnCount = Wave2_Pool.Num();
		break;
	case 3:
		SpawnCount = Wave3_Pool.Num();
		break;
	}
	
	return SpawnCount;
}
