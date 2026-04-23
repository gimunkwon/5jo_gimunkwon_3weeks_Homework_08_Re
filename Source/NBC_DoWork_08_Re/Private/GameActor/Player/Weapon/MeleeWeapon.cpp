#include "GameActor/Player/Weapon/MeleeWeapon.h"



AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackDamage = 50.f;
}


void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

