#include "GameActor/Enemy/AIController/BTT_AttackToPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameActor/Enemy/MyZombie.h"

UBTT_AttackToPlayer::UBTT_AttackToPlayer()
{
}

EBTNodeResult::Type UBTT_AttackToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	APawn* ControllingPawn = AIController->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bCanAttackRange"),false);
	
	if (AMyZombie* MyAIOwner = Cast<AMyZombie>(ControllingPawn))
	{
		MyAIOwner->AttackToPlayer(Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"))));
	}
	
	
	return EBTNodeResult::Succeeded;
}
