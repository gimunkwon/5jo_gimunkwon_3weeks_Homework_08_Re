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

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ammo")
	int32 MaxAmmo;
	int32 CurrentAmmo;
	
public:
	virtual void Tick(float DeltaTime) override;
};
