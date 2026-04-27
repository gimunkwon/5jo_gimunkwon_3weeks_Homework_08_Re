#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "Components/WidgetComponent.h"
#include "DataTable/Zombie/DT_ZombieStat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Enemy/EnemyStatWidget.h"


AMyZombie::AMyZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Zombie");
	
	WidgetC_EnemyStat = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetC_EnemyStat->SetupAttachment(RootComponent);
	WidgetC_EnemyStat->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetC_EnemyStat->SetPivot(FVector2D(0.5f,0.f));
	WidgetC_EnemyStat->SetRelativeLocation(FVector(0.f,0.f,120.f));
	
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Overlap);
}

void AMyZombie::AttackToPlayer(AActor* Attacked_Actor)
{
	UE_LOG(LogTemp,Warning,TEXT("좀비 공격 시작!!"));
	UGameplayStatics::ApplyDamage(Attacked_Actor, 10.f, nullptr,this, UDamageType::StaticClass());
}

void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
	
	WidgetC_EnemyStat->SetWidgetClass(Widget_EnemyStat);
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
	
	DrawDebugSphere(GetWorld(),GetActorLocation(), 150.f, 32, FColor::Blue, false, -1.f, 0, 1.f);
}


