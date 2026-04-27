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
	
	FORCEINLINE float GetStartDistance() const {return Distance;}
	FORCEINLINE FVector GetAttackSize() const {return AttackSize;}
protected:
	virtual void BeginPlay() override;
	void InitializeWeaponStat() override;
	
	float Distance;
	FVector AttackSize;
public:
	virtual void Tick(float DeltaTime) override;
};
