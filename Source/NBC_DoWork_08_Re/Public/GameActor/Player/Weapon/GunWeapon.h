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

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
