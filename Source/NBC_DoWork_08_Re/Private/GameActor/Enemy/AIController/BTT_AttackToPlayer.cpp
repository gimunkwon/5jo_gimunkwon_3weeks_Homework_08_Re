#include "GameActor/Enemy/AIController/BTT_AttackToPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_AttackToPlayer::UBTT_AttackToPlayer()
{
}

EBTNodeResult::Type UBTT_AttackToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	APawn* ControllingPawn = AIController->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;
	
	UE_LOG(LogTemp,Warning,TEXT("좀비 공격 시작"));
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bCanAttackRange"),false);
	
	return EBTNodeResult::Succeeded;
}
