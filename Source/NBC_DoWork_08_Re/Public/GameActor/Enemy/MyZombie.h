#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyZombie.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AMyZombie : public ACharacter
{
	GENERATED_BODY()

public:
	AMyZombie();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
