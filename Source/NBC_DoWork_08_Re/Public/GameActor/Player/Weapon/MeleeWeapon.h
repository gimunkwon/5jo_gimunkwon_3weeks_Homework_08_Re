#pragma once

#include "CoreMinimal.h"
#include "MyWeapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AMeleeWeapon : public AMyWeapon
{
	GENERATED_BODY()

public:
	
	AMeleeWeapon();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
