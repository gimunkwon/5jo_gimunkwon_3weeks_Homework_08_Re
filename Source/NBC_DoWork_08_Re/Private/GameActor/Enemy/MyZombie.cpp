#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "Components/WidgetComponent.h"


AMyZombie::AMyZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Zombie");
	
	WidgetC_EnemyStat = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	// WidgetC_EnemyStat->SetupAttachment(GetMesh());
	// WidgetC_EnemyStat->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
}

float AMyZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


