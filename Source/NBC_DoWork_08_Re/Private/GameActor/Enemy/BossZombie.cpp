// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Enemy/BossZombie.h"


// Sets default values
ABossZombie::ABossZombie()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABossZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABossZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

