#include "NBC_DoWork_08_Re/Public/GameActor/Player/MyPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
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
}


void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
			EnhancedInputComp->BindAction(PC->IA_Move,ETriggerEvent::Triggered,this,&AMyPlayer::Move);
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