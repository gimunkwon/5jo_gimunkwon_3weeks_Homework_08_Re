#include "Object/GateToNextWave.h"

#include "Global/MyGameState.h"


AGateToNextWave::AGateToNextWave()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
}


void AGateToNextWave::BeginPlay()
{
	Super::BeginPlay();
	if (AMyGameState* GS = Cast<AMyGameState>(GetWorld()->GetGameState()))
	{
		GS->RegisterWaveGate(this);
	}
}


void AGateToNextWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

