#pragma once

#include "CoreMinimal.h"
#include "MyWeapon.h"
#include "GunWeapon.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AGunWeapon : public AMyWeapon
{
	GENERATED_BODY()

public:
	AGunWeapon();
	
	bool bIsfire();
	bool bCanReload();
	FORCEINLINE int32 GetCurrentAmmo() const {return CurrentAmmo;}
	FORCEINLINE int32 GetMaxAmmo() const {return MaxAmmo;}
	FORCEINLINE float GetLastFireTime() const {return LastFireTime;}
	FORCEINLINE float GetGunMaxDistance() const {return MaxDistance;}
	FORCEINLINE float GetFireRate() const {return FireRate;}
	
	FORCEINLINE void SetLastFireTime(float NewLastFireTime) {LastFireTime = NewLastFireTime;}
protected:
	virtual void BeginPlay() override;
	
	void InitializeWeaponStat() override;
	
	int32 MaxAmmo;
	int32 CurrentAmmo;
	
	float FireRate;
	float LastFireTime;
	float MaxDistance;
public:
	virtual void Tick(float DeltaTime) override;
};
