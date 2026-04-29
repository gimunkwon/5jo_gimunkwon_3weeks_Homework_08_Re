#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "KismetTraceUtils.h"
#include "Components/CapsuleComponent.h"
#include "Engine/OverlapResult.h"
#include "GameActor/Player/Animations/MyPlayerAnimInst.h"
#include "GameActor/Player/Weapon/GunWeapon.h"
#include "GameActor/Player/Weapon/MeleeWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global/MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NBC_DoWork_08_Re/Public/GameActor/Player/Controller/MyPlayerController.h"
#include "UI/Player/PlayerHUDWidget.h"


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
	SpringArmComp->bDoCollisionTest = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	PlayerBattleState = EPlayerBattleState::Melee;
	InterpSpeed = 30.f;
	MaxHP = 100.f;
	CurrentHP = MaxHP;
	bIsDead = false;
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeWeapon(MeleeWeapon,EPlayerBattleState::Melee);
	InitializeWeapon(GunWeapon,EPlayerBattleState::Gun);
	
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
	{
		PC->WidgetInst_HUD->UpdatePlayerHPBar(MaxHP, CurrentHP);
		PC->WidgetInst_HUD->UpdateSelectBorder(PlayerBattleState);
	}
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
			if (PC->IA_Rotate)
			{
				EnhancedInputComp->BindAction(PC->IA_Rotate,ETriggerEvent::Triggered,this,&AMyPlayer::Rotate);
				EnhancedInputComp->BindAction(PC->IA_Rotate,ETriggerEvent::Completed,this,&AMyPlayer::EndRotate);
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

void AMyPlayer::Rotate()
{
	// UE_LOG(LogTemp,Warning,TEXT("회전 시작"));
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
	{
		FHitResult HitResult;
		if (PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult))
		{
			FVector StartPos = GetActorLocation();
			FVector TargetPos = HitResult.Location;
			
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartPos,TargetPos);
			FRotator NewRotation(0.f,LookAtRotation.Yaw,0.f);
			
			FRotator CurrentRoation = GetActorRotation();
			FRotator SmoothRotation = FMath::RInterpTo(CurrentRoation, NewRotation, GetWorld()->GetDeltaSeconds(), InterpSpeed);
			
			GetCharacterMovement()->bOrientRotationToMovement = false;
			SetActorRotation(SmoothRotation);
		}
	}
}

void AMyPlayer::EndRotate()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
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
		
		if (BattleState == EPlayerBattleState::Gun)
		{
			if (AGunWeapon* WeaponGun = Cast<AGunWeapon>(SpawnedWeapon))
			{
				if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
				{
					PC->WidgetInst_HUD->UpdateAmmoText(WeaponGun->GetCurrentAmmo(), WeaponGun->GetMaxAmmo());
				}
			}
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
	
	
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	if (!PC) return;
	
	// 기존 무기가 있을경우 숨겨야함
	if (WeaponMap.Contains(PlayerBattleState))
	{
		WeaponMap[PlayerBattleState]->SetActorHiddenInGame(true);
	}
	
	if (WeaponMap.Contains(NewState))
	{
		WeaponMap[NewState]->SetActorHiddenInGame(false);
		PlayerBattleState = NewState;
		PC->WidgetInst_HUD->UpdateSelectBorder(PlayerBattleState);
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
	AGunWeapon* CurrentGun = nullptr;
	
	if (WeaponMap.Contains(EPlayerBattleState::Gun))
	{
		CurrentGun = Cast<AGunWeapon>(WeaponMap[EPlayerBattleState::Gun]);
	}
	
	if (!CurrentGun) return;
	if (CurrentGun->GetCurrentAmmo() == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("탄약없음 재장전 필요"));
		return;
	}
	
	float CurrentTime = GetWorld()->GetTimeSeconds();
	
	if (CurrentTime - CurrentGun->GetLastFireTime() >= CurrentGun->GetFireRate())
	{
		if (AM_GunAttack)
		{
			MyAnimInst->Montage_Play(AM_GunAttack);
		}
		UE_LOG(LogTemp,Warning,TEXT("총 발사"));
		CurrentGun->SetLastFireTime(CurrentTime);
		
		if (WeaponMap.Contains(PlayerBattleState))
		{
			if (AGunWeapon* WeaponGun = Cast<AGunWeapon>(WeaponMap[PlayerBattleState]))
			{
				FVector StartPos = WeaponGun->GetWeaponMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
				FVector LaunchDir = WeaponGun->GetWeaponMesh()->GetSocketRotation(TEXT("MuzzleSocket")).Vector();
				float MaxDistance = CurrentGun->GetGunMaxDistance();
				FVector EndPos = StartPos + (LaunchDir * MaxDistance);
					
				WeaponGun->bIsfire();
				UE_LOG(LogTemp,Warning,TEXT("Current Ammo: %d"),WeaponGun->GetCurrentAmmo());
				
				if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
				{
					PC->WidgetInst_HUD->UpdateAmmoText(WeaponGun->GetCurrentAmmo(), WeaponGun->GetMaxAmmo());
				}
				
				CheckGunAttackRange(CurrentGun,StartPos, EndPos);
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
	
	FOnMontageEnded EndMontage;
	EndMontage.BindUObject(this, &AMyPlayer::EndAttackMontage);
	MyAnimInst->Montage_SetEndDelegate(EndMontage,AM_MeleeAttack);
}

void AMyPlayer::CheckMeleeAttackRange()
{
	AMeleeWeapon* CurrentMeleeWeapon = nullptr;
	if (WeaponMap.Contains(EPlayerBattleState::Melee))
	{
		CurrentMeleeWeapon = Cast<AMeleeWeapon>(WeaponMap[EPlayerBattleState::Melee]);
	}
	if (!CurrentMeleeWeapon) return;
	
	FVector Center = GetActorLocation() + (GetActorForwardVector() * CurrentMeleeWeapon->GetStartDistance());
	FVector BoxExtent = CurrentMeleeWeapon->GetAttackSize();
	FQuat Rotation = GetActorRotation().Quaternion();
	
	FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxExtent);
	
	TArray<FOverlapResult> OverlapsResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapsResults,Center,Rotation,ECC_GameTraceChannel1, BoxShape,Params);
	UE_LOG(LogTemp,Warning,TEXT("전체 히트 개수 : %d"),OverlapsResults.Num());
	DrawDebugBox(GetWorld(), Center, BoxExtent, Rotation, bHit ? FColor::Red : FColor::Yellow, false, 0.5f, 0, 1.f);
	
	if (!OverlapsResults.IsEmpty())
	{
		TArray<AActor*> AlreadyAttackActor;
		for (auto& Result : OverlapsResults)
		{
			if (!AlreadyAttackActor.Contains(Result.GetActor()) && Result.GetActor()->ActorHasTag(TEXT("Zombie")))
			{
				UE_LOG(LogTemp,Warning,TEXT("공격 받은 대상 %s"),*Result.GetActor()->GetName());
				UGameplayStatics::ApplyDamage(Result.GetActor(), CurrentMeleeWeapon->GetAttackDamage(), GetController(), this, UDamageType::StaticClass());
				AlreadyAttackActor.Add(Result.GetActor());
			}
		}
	}
}

void AMyPlayer::CheckGunAttackRange(AGunWeapon* CurrentGunWeapon, FVector StartLocation, FVector EndLocation)
{
	TArray<FHitResult> HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
	UE_LOG(LogTemp,Warning,TEXT("전체 히트 개수: %d"),HitResult.Num());
	
	if (!HitResult.IsEmpty())
	{
		TArray<AActor*> AlreadyHitActor;
		
		for (const FHitResult& Result : HitResult)
		{
			AActor* HitActor = Result.GetActor();
			if (HitActor && !AlreadyHitActor.Contains(HitActor) && HitActor->ActorHasTag(TEXT("Zombie")))
			{
				UE_LOG(LogTemp,Warning,TEXT("총 관통 타격 횟수: %s"), *HitActor->GetName());
				UGameplayStatics::ApplyDamage(Result.GetActor(), CurrentGunWeapon->GetAttackDamage(), GetController(), this, UDamageType::StaticClass());
				AlreadyHitActor.Add(HitActor);
			}
		}
	}
	DrawDebugLine(GetWorld(),StartLocation, EndLocation, bHit ? FColor::Red : FColor::Green, false, 0.5f, 0, 1.f);
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
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
		{
			PC->WidgetInst_HUD->UpdateAmmoText(WeaponGun->GetCurrentAmmo(),WeaponGun->GetMaxAmmo());
		}
	}
}

float AMyPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CurrentHP = FMath::Clamp(CurrentHP - ActualDamage, 0.f, MaxHP);
	if (CurrentHP <= 0.f) OnDead();
	
	UE_LOG(LogTemp,Warning,TEXT("플레이어 공격 받음 현재 HP %f"),CurrentHP);
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
	{
		PC->WidgetInst_HUD->UpdatePlayerHPBar(MaxHP, CurrentHP);
	}
	
	return ActualDamage;
}

void AMyPlayer::OnDead()
{
	if (bIsDead) return;
	bIsDead = true;
	UE_LOG(LogTemp,Warning,TEXT("플레이어 사망..."));
	
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	
	if (UMyPlayerAnimInst* AnimInst = Cast<UMyPlayerAnimInst>(GetMesh()->GetAnimInstance()))
	{
		AnimInst->bIsPlayerDead = true;
	}
	
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
	{
		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
		DisableInput(PC);
	}
	
	if (AMyGameState* GS = Cast<AMyGameState>(GetWorld()->GetGameState()))
	{
		GS->GameOver(true);
	}
}