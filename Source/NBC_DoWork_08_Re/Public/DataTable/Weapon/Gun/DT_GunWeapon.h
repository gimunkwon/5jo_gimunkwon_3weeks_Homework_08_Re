#pragma once

#include "CoreMinimal.h"
#include "DataTable/Weapon/DT_BaseWeapon.h"
#include "DT_GunWeapon.generated.h"

USTRUCT(BlueprintType)
struct FGunWeaponStat : public FBaseWeaponStat
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GunStat")
	float MaxDistance;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GunStat")
	float FireRate;
};