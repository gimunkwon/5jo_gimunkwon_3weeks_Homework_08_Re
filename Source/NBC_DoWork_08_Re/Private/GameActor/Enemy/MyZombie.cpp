#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "Components/WidgetComponent.h"
#include "DataTable/Zombie/DT_ZombieStat.h"
#include "UI/Enemy/EnemyStatWidget.h"


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
	
	InitializeStat(EZombieType::Normal);
	
	if (WidgetC_EnemyStat)
	{
		UEnemyStatWidget* HPWidget = Cast<UEnemyStatWidget>(WidgetC_EnemyStat->GetWidget());
		if (HPWidget)
		{
			HPWidget->UpdateHPProgressBar(HP, MaxHP);
		}
	}
}

void AMyZombie::InitializeStat(EZombieType ZombieType)
{
	ZombieTypes = ZombieType;
	if (!DT_Stat)
	{
		UE_LOG(LogTemp,Warning,TEXT("Not Yet"));
		return;
	}
	
	static const FString ContextString = TEXT("DataTableInitialize");
	TArray<FZombieStat*> ZombieStats;
	
	DT_Stat->GetAllRows(ContextString,ZombieStats);
	
	const UEnum* EnumPtr = StaticEnum<EZombieType>();
	FString EnumToStrngText = "";
	if (EnumPtr)
	{
		EnumToStrngText = EnumPtr->GetNameStringByValue((int64)ZombieType);
		UE_LOG(LogTemp,Warning,TEXT("Zombie Type %s"),*EnumToStrngText);
	}

	switch (ZombieType)
	{
	case EZombieType::Normal:
		MaxHP = DT_Stat->FindRow<FZombieStat>(*EnumToStrngText, ContextString)->MaxHP;
		HP = MaxHP;
		break;
	case EZombieType::Running:
		MaxHP = DT_Stat->FindRow<FZombieStat>(*EnumToStrngText, ContextString)->MaxHP;
		HP = MaxHP;
		break;
	case EZombieType::Boss:
		MaxHP = DT_Stat->FindRow<FZombieStat>(*EnumToStrngText, ContextString)->MaxHP;
		HP = MaxHP;
		break;
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


