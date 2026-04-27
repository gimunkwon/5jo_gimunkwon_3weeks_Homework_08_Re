#pragma once

#include "CoreMinimal.h"
#include "DT_BaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FBaseWeaponStat : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponStat")
	FName WeaponName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponStat")
	float WeaponAtkDamage;
};
