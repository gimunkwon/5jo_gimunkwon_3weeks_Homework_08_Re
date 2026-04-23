#include "GameActor/Player/Animations/MyPlayerAnimInst.h"

#include "GameActor/Player/MyPlayer.h"

void UMyPlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (!MyOwnerInst)
	{
		MyOwnerInst = Cast<AMyPlayer>(TryGetPawnOwner());
	}
}

void UMyPlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MyOwnerInst)
	{
		FVector Velocity = MyOwnerInst->GetVelocity();
		PlayerSpeed = Velocity.Size2D();
		CurrentBattleState = MyOwnerInst->GetPlayerBattleState();
	}
}


