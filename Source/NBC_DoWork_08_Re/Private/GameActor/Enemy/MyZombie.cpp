#include "NBC_DoWork_08_Re/Public/GameActor/Enemy/MyZombie.h"

#include "BrainComponent.h"
#include "AI/NavigationSystemBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "DataTable/Zombie/DT_ZombieStat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Enemy/EnemyStatWidget.h"
#include "Engine/OverlapResult.h"
#include "GameActor/Enemy/AIController/AIZombieController.h"


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

void AMyZombie::BeginPlay()
{
	Super::BeginPlay();
	
	WidgetC_EnemyStat->SetWidgetClass(Widget_EnemyStat);
	
	if (WidgetC_EnemyStat)
	{
		UEnemyStatWidget* HPWidget = Cast<UEnemyStatWidget>(WidgetC_EnemyStat->GetWidget());
		if (HPWidget)
		{
			HPWidget->UpdateHPProgressBar(HP, MaxHP);
		}
	}
}

void AMyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DrawDebugSphere(GetWorld(),GetActorLocation(), 150.f, 32, FColor::Blue, false, -1.f, 0, 1.f);
}

void AMyZombie::InitializeStat(const FDataTableRowHandle& RowHandle)
{
	if (RowHandle.IsNull()) return;
	UE_LOG(LogTemp,Warning,TEXT("좀비 스탯 초기화중..."));
	
	static const FString ZombieContextString = "ZombieDataTable Initialize";
	
	FZombieStat* ZombieRow = RowHandle.GetRow<FZombieStat>(ZombieContextString);
	if (ZombieRow)
	{
		MaxHP = ZombieRow->MaxHP;
		HP = MaxHP;
		AttackRange = ZombieRow->AttackRange;
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
	
	if (HP <= 0.f)
	{
		OnDead();
	}
	
	return ActualDamage;
}

void AMyZombie::OnDead()
{
	UE_LOG(LogTemp,Warning,TEXT("Zombie 사망!!"));
	
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC && AIC->GetBrainComponent())
	{
		AIC->GetBrainComponent()->StopLogic(TEXT("Zombie is Dead"));
	}
	
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//TODO:: Death애님 몽타주 실행
	if (AM_Dead)
	{
		if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
		{
			AnimInst->Montage_Play(AM_Dead);
			FOnMontageEnded EndMontage;
			EndMontage.BindLambda([this](UAnimMontage* Montage, bool bInterrupted){Destroy();});
			AnimInst->Montage_SetEndDelegate(EndMontage,AM_Dead);
		}
	}
	
	SetLifeSpan(3.f);
}

void AMyZombie::AttackToPlayer(AActor* Attacked_Actor)
{
	UE_LOG(LogTemp,Warning,TEXT("좀비 공격 시작!!"));
	
	if (AM_Attack)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AM_Attack);
	}
}

void AMyZombie::ZombieAttackHitCheck()
{
	if (AAIZombieController* AIC = Cast<AAIZombieController>(GetController()))
	{
		static const FString ContextString = "ZombieAttackStat";
		FZombieStat* ZombieStatRow = AIC->GetRowHandle().GetRow<FZombieStat>(ContextString);
		if (ZombieStatRow)
		{
			FVector StartPos = GetActorLocation() + (GetActorForwardVector() * ZombieStatRow->AttackRange);
			FVector BoxExtent = ZombieStatRow->AttackBoxSize;
			FQuat Rot = GetActorRotation().Quaternion();
			FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxExtent);
			TArray<FOverlapResult> OverlapsArray;
		
			GetWorld()->OverlapMultiByChannel(OverlapsArray,StartPos, Rot, ECC_GameTraceChannel2, BoxShape);
			DrawDebugBox(GetWorld(),StartPos, BoxExtent, FColor::Yellow, false, 2.f, 0, 1.f);
		
			TArray<AActor*> AlreadyAttackedActors;
		
			for (const auto& OverlapResult : OverlapsArray)
			{
				if (!AlreadyAttackedActors.Contains(OverlapResult.GetActor()) && OverlapResult.GetActor()->ActorHasTag(TEXT("Player")))
				{
					UE_LOG(LogTemp,Warning,TEXT("좀비 공격 시작!!"));
					UGameplayStatics::ApplyDamage(OverlapResult.GetActor(), ZombieStatRow->AttackDamage, nullptr, this, UDamageType::StaticClass());
					AlreadyAttackedActors.Add(OverlapResult.GetActor());
				}
			
			}
		}
	}
}