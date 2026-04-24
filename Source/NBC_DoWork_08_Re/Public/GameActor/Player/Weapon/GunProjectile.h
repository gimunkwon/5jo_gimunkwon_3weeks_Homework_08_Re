#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunProjectile.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AGunProjectile : public AActor
{
	GENERATED_BODY()

public:
	
	AGunProjectile();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
