#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AMyWeapon : public AActor
{
	GENERATED_BODY()

public:
	
	AMyWeapon();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
