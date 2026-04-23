#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"



AMyZombie::AMyZombie()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
}


void AMyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMyZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

