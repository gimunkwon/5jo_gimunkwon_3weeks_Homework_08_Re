#include "GameActor/Enemy/AIController/AIZombieController.h"



AAIZombieController::AAIZombieController()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AAIZombieController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIZombieController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (RunBehaviorTree(BT_Data))
	{
		UE_LOG(LogTemp,Warning,TEXT("비헤이비어트리 작동"));
	}
}


void AAIZombieController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

