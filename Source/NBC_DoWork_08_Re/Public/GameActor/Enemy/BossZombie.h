// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyZombie.h"
#include "BossZombie.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API ABossZombie : public AMyZombie
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
