#include "GameActor/Player/Weapon/MyWeapon.h"

#include "DataTable/Weapon/DT_BaseWeapon.h"


AMyWeapon::AMyWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	
}


void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeWeaponStat();
}

void AMyWeapon::InitializeWeaponStat()
{
	if (RowHandle.IsNull()) return;
	UE_LOG(LogTemp,Warning,TEXT("무기 스탯 초기화중..."));
	
	static const FString ContextString = "Initialize WeaponDataTable";
	FBaseWeaponStat* FindRow = RowHandle.GetRow<FBaseWeaponStat>(ContextString);
	
	if (FindRow)
	{
		WeaponName = FindRow->WeaponName;
		AttackDamage = FindRow->WeaponAtkDamage;
		UE_LOG(LogTemp,Warning,TEXT("무기 기본스탯 초기화 완료"));
	}
	
	
}


void AMyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

