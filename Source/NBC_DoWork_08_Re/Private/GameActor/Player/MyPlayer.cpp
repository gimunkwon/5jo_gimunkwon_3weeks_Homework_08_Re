#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "AI/NavigationSystemBase.h"
#include "Engine/StaticMeshSocket.h"
#include "GameActor/Player/Weapon/GunWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"


AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 600.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	PlayerBattleState = EPlayerBattleState::Melee;
	
	FireRate = 0.2f;
	LastFireTime = 0.f;
}


void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeWeapon(MeleeWeapon,EPlayerBattleState::Melee);
	InitializeWeapon(GunWeapon,EPlayerBattleState::Gun);
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (AMyPlayerController* PC =  Cast<AMyPlayerController>(GetController()))
		{
			if (PC->IA_Move)
			{
				EnhancedInputComp->BindAction(PC->IA_Move,ETriggerEvent::Triggered,this,&AMyPlayer::Move);
			}
				
			if (PC->IA_SelectBattleMode)
			{
				EnhancedInputComp->BindAction(PC->IA_SelectBattleMode,ETriggerEvent::Triggered,this,&AMyPlayer::SelectWeapon);
			}
			
			if (PC->IA_Attack)
			{
				EnhancedInputComp->BindAction(PC->IA_Attack,ETriggerEvent::Triggered,this,&AMyPlayer::Attack);
			}
			
			if (PC->IA_Reload)
			{
				EnhancedInputComp->BindAction(PC->IA_Reload,ETriggerEvent::Started,this,&AMyPlayer::Reload);
			}
		}
	}
	
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
	if (bIsAttacking) return;
	
	FVector MoveValue = Value.Get<FVector>();
	
	if (!FMath::IsNearlyZero(MoveValue.Y))
	{
		AddMovementInput(FVector(MoveValue.Y,0.f,0.f),1.f);
	}
	if (!FMath::IsNearlyZero(MoveValue.X))
	{
		AddMovementInput(FVector(0.f,MoveValue.X,0.f),1.f);
	}
	
}

void AMyPlayer::InitializeWeapon(TSubclassOf<AActor> WeaponClass, EPlayerBattleState BattleState)
{
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = this;
		
		AActor* SpawnedWeapon = GetWorld()->SpawnActor<AActor>(WeaponClass,SpawnParam);
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,true);
		
		FName SocketName = (BattleState == EPlayerBattleState::Melee) ? TEXT("WeaponSocket") : TEXT("GunSocket");
		
		SpawnedWeapon->AttachToComponent(GetMesh(),AttachmentRules,SocketName);		
		
		WeaponMap.Add(BattleState,SpawnedWeapon);
		
		if (PlayerBattleState == BattleState)
		{
			SpawnedWeapon->SetActorHiddenInGame(false);
		}
		else
		{
			SpawnedWeapon->SetActorHiddenInGame(true);
		}
	}
}

void AMyPlayer::SelectWeapon(const FInputActionValue& Value)
{
	if (bIsAttacking) return;
	
	int32 SlotIndex = static_cast<int>(Value.Get<float>());
	
	EPlayerBattleState NewState = (SlotIndex == 1) ? EPlayerBattleState::Melee : EPlayerBattleState::Gun;
	
	// 같은 키를 눌렀을때
	if (PlayerBattleState == NewState) return;
	
	// 기존 무기가 있을경우 숨겨야함
	if (WeaponMap.Contains(PlayerBattleState))
	{
		WeaponMap[PlayerBattleState]->SetActorHiddenInGame(true);
	}
	
	if (WeaponMap.Contains(NewState))
	{
		WeaponMap[NewState]->SetActorHiddenInGame(false);
		PlayerBattleState = NewState;
	}
	
}

void AMyPlayer::Attack()
{
	UAnimInstance* MyAnimInst = GetMesh()->GetAnimInstance();
	if (!MyAnimInst) return;
	// UE_LOG(LogTemp,Warning,TEXT("플레이어 공격 시작"));
	
	if (PlayerBattleState == EPlayerBattleState::Melee)
	{
		MeleeAttack(MyAnimInst);
	}
	else if (PlayerBattleState == EPlayerBattleState::Gun)
	{
		GunAttack(MyAnimInst);
	}
}

void AMyPlayer::GunAttack(UAnimInstance* MyAnimInst)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastFireTime >= FireRate)
	{
		if (AM_GunAttack)
		{
			MyAnimInst->Montage_Play(AM_GunAttack);
		}
		UE_LOG(LogTemp,Warning,TEXT("총 발사"));
		LastFireTime = CurrentTime;
			
		//TODO:: 총알 발사 로직
		if (WeaponMap.Contains(PlayerBattleState))
		{
			if (AGunWeapon* WeaponGun = Cast<AGunWeapon>(WeaponMap[PlayerBattleState]))
			{
				FVector StartPos = WeaponGun->GetWeaponMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
				FVector LaunchDir = WeaponGun->GetWeaponMesh()->GetSocketRotation(TEXT("MuzzleSocket")).Vector();
					
				float MaxDistance = 1000.f;
				FVector EndPos = StartPos + (LaunchDir * MaxDistance);
					
				WeaponGun->bIsfire();
				UE_LOG(LogTemp,Warning,TEXT("Current Ammo: %d"),WeaponGun->GetCurrentAmmo());
				DrawDebugLine(GetWorld(),StartPos, EndPos,FColor::Red,false,0.5f,0,1.f);
			}
		}
	}
}

void AMyPlayer::MeleeAttack(UAnimInstance* MyAnimInst)
{
	if (bIsAttacking) return;
	if (!AM_MeleeAttack) return;
		
	bIsAttacking = true;
		
	GetCharacterMovement()->StopMovementImmediately();
	MyAnimInst->Montage_Play(AM_MeleeAttack);
		
	//TODO:: MeleeWeapon 공격로직 
		
	FOnMontageEnded EndMontage;
	EndMontage.BindUObject(this, &AMyPlayer::EndAttackMontage);
	MyAnimInst->Montage_SetEndDelegate(EndMontage,AM_MeleeAttack);
}

void AMyPlayer::EndAttackMontage(UAnimMontage* Montage, bool bIsEnd)
{
	bIsAttacking = false;
	UE_LOG(LogTemp,Warning,TEXT("애님몽타주 종료 이동 가능!!"));
}

void AMyPlayer::Reload()
{
	if (PlayerBattleState != EPlayerBattleState::Gun) return;
	
	AGunWeapon* WeaponGun = nullptr;
	if (WeaponMap.Contains(PlayerBattleState))
	{
		WeaponGun = Cast<AGunWeapon>(WeaponMap[PlayerBattleState]);
	}
	if (WeaponGun)
	{
		WeaponGun->bCanReload();
	}
}

