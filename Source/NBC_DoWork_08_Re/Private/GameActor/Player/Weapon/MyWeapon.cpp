#include "GameActor/Player/Weapon/MyWeapon.h"



AMyWeapon::AMyWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	
	AttackDamage = 0.f;
}


void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

