#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"



AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

