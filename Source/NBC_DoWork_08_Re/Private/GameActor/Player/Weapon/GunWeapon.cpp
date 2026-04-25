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

bool AGunWeapon::bCanReload()
{
	if (CurrentAmmo == MaxAmmo) return false;
	
	CurrentAmmo = MaxAmmo;
	UE_LOG(LogTemp,Warning,TEXT("Reload!! CurrentAmmo : %d"),CurrentAmmo);
	return true;
}


void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

