#include "GameActor/Player/Weapon/GunWeapon.h"



AGunWeapon::AGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackDamage = 100.f;
	
	MaxAmmo = 30;
	CurrentAmmo = MaxAmmo;
}

bool AGunWeapon::bIsfire()
{
	if (CurrentAmmo > 0) CurrentAmmo--;
	return CurrentAmmo > 0;
}


void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

