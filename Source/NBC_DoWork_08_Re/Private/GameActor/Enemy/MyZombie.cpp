#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "Components/WidgetComponent.h"
#include "DataTable/Zombie/DT_ZombieStat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Enemy/EnemyStatWidget.h"


AMyZombie::AMyZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Zombie");
	
	WidgetC_EnemyStat = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
}

void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeStat();
	
	if (WidgetC_EnemyStat)
	{
		UEnemyStatWidget* HPWidget = Cast<UEnemyStatWidget>(WidgetC_EnemyStat->GetWidget());
		if (HPWidget)
		{
			HPWidget->UpdateHPProgressBar(HP, MaxHP);
		}
	}
}

void AMyZombie::InitializeStat()
{
	if (RowHandle.IsNull()) return;
	UE_LOG(LogTemp,Warning,TEXT("좀비 스탯 초기화중..."));
	
	static const FString ZombieContextString = "ZombieDataTable Initialize";
	
	FZombieStat* ZombieRow = RowHandle.GetRow<FZombieStat>(ZombieContextString);
	if (ZombieRow)
	{
		MaxHP = ZombieRow->MaxHP;
		HP = MaxHP;
		GetCharacterMovement()->MaxWalkSpeed = ZombieRow->MaxWalkSpeed;
	}
}

float AMyZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HP = FMath::Clamp(HP - ActualDamage, 0.f, MaxHP);
	UE_LOG(LogTemp,Warning,TEXT("Current Enemy HP : %f"),HP);
	
	// WidgetUpdate 로직
	if (WidgetC_EnemyStat)
	{
		UEnemyStatWidget* HPWidget = Cast<UEnemyStatWidget>(WidgetC_EnemyStat->GetWidget());
		if (HPWidget)
		{
			HPWidget->UpdateHPProgressBar(HP, MaxHP);
		}
	}
	return ActualDamage;
}

void AMyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


