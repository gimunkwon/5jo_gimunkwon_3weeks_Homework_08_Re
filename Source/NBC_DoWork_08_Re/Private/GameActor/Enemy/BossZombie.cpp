#include "GameActor/Enemy/BossZombie.h"


ABossZombie::ABossZombie()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void ABossZombie::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABossZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABossZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

