#include "GameActor/Player/Weapon/GunWeapon.h"

#include "DataTable/Weapon/Gun/DT_GunWeapon.h"


AGunWeapon::AGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeWeaponStat();
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

void AGunWeapon::InitializeWeaponStat()
{
	Super::InitializeWeaponStat();
	
	static const FString GunWeaponContextString = "InitializeGunWeapon";
	FGunWeaponStat* GunWeaponRow = RowHandle.GetRow<FGunWeaponStat>(GunWeaponContextString);
	
	if (GunWeaponRow)
	{
		MaxAmmo = GunWeaponRow->MaxAmmo;
		CurrentAmmo = MaxAmmo;
		FireRate = GunWeaponRow->FireRate;
		MaxDistance = GunWeaponRow->MaxDistance;
		UE_LOG(LogTemp,Warning,TEXT("총 무기 초기화 완료..."));
	}
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

