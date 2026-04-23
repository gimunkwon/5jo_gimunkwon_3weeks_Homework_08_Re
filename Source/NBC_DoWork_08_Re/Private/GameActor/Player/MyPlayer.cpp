#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
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
}


void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerWeapon)
	{
		SpawnWeapon();
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
		}
	}
	
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
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

void AMyPlayer::SpawnWeapon()
{
	if (PlayerWeapon)
	{
		AActor* SpawnActorInst = GetWorld()->SpawnActor<AActor>(PlayerWeapon,FVector::ZeroVector,FRotator::ZeroRotator);	
		if (SpawnActorInst)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,true);
			SpawnActorInst->AttachToComponent(GetMesh(),AttachmentRules,TEXT("WeaponSocket"));
		}
	}
}

void AMyPlayer::SelectWeapon(const FInputActionValue& Value)
{
	int32 SlotIndex = static_cast<int>(Value.Get<float>());
	
	switch (SlotIndex)
	{
	case 1:
		{
			PlayerBattleState = EPlayerBattleState::Melee;
			UE_LOG(LogTemp,Warning,TEXT("근접 무기 모드"));
		}
		break;
	case 2:
		{
			PlayerBattleState = EPlayerBattleState::Gun;
			UE_LOG(LogTemp,Warning,TEXT("원거리 무기 모드"));
		}
		break;
	default:
		break;
	}
}