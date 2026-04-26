#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "Components/WidgetComponent.h"


AMyZombie::AMyZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Zombie");
	
	WidgetC_EnemyStat = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	// WidgetC_EnemyStat->SetupAttachment(GetMesh());
	// WidgetC_EnemyStat->SetWidgetSpace(EWidgetSpace::Screen);
	
	MaxHP = 200.f;
	HP = 200.f;
}

void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
}

float AMyZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	HP = FMath::Clamp(HP - ActualDamage, 0.f, MaxHP);
	UE_LOG(LogTemp,Warning,TEXT("Current Enemy HP : %f"),HP);
	
	
	return ActualDamage;
}

void AMyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


