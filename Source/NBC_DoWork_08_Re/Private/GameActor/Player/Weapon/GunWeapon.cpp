#include "GameActor/Player/Weapon/GunWeapon.h"



AGunWeapon::AGunWeapon()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

