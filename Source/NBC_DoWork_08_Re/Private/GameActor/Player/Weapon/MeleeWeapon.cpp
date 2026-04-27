#include "GameActor/Player/Weapon/MeleeWeapon.h"

#include "DataTable/Weapon/Melee/DT_MeleeWeapon.h"


AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeWeaponStat();
}

void AMeleeWeapon::InitializeWeaponStat()
{
	Super::InitializeWeaponStat();
	
	static const FString MeleeContextString = "Initialize MeleeWeapon";
	FMeleeWeaponStat* MeleeWeaponRow = RowHandle.GetRow<FMeleeWeaponStat>(MeleeContextString);
	
	if (MeleeWeaponRow)
	{
		AttackSize = MeleeWeaponRow->BoxExtent;
		UE_LOG(LogTemp,Warning,TEXT("근접무기 스탯 초기화 완료..."));
	}
}


void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

