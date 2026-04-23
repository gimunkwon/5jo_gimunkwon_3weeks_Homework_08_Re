#include "GameActor/Player/Weapon/MyWeapon.h"



AMyWeapon::AMyWeapon()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

