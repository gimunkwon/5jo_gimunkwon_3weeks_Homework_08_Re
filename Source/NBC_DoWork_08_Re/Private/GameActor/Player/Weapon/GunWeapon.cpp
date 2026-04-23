#include "GameActor/Player/Weapon/GunWeapon.h"



AGunWeapon::AGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackDamage = 100.f;
}


void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

