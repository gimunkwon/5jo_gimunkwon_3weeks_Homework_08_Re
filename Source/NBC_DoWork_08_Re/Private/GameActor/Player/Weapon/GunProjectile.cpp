#include "GameActor/Player/Weapon/GunProjectile.h"



AGunProjectile::AGunProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}


void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
}


void AGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

