#include "GameActor/Player/Weapon/GunProjectile.h"



AGunProjectile::AGunProjectile()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

