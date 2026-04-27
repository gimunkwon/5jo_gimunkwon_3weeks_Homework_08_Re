#include "GameActor/Enemy/AIController/BTT_AttackToPlayer.h"

#include "AIController.h"

UBTT_AttackToPlayer::UBTT_AttackToPlayer()
{
	AttackRange = 500.f;
}

EBTNodeResult::Type UBTT_AttackToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	APawn* ControllingPawn = AIController->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;
	
	
	
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
