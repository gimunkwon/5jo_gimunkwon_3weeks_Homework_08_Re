#include "GameActor/Enemy/Animations/ZombieAnimInst.h"

#include "GameActor/Enemy/MyZombie.h"

void UZombieAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (!MyOwner)
	{
		MyOwner = Cast<AMyZombie>(TryGetPawnOwner());
	}
}

void UZombieAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MyOwner)
	{
		FVector Velocity = MyOwner->GetVelocity();
		GroundSpeed = Velocity.Size2D();
	}
}
