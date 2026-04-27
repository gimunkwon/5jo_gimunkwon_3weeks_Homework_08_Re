#pragma once

#include "CoreMinimal.h"
#include "MyZombie.h"
#include "BossZombie.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API ABossZombie : public AMyZombie
{
	GENERATED_BODY()

public:
	
	ABossZombie();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
