#include "GameActor/Enemy/AIController/BTT_FindPlayerLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindPlayerLocation::UBTT_FindPlayerLocation()
{
	SearchRadius = 1000.f;
	
	NodeName = TEXT("Find Random Location");
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_FindPlayerLocation, TargetLocationKey));
}

EBTNodeResult::Type UBTT_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	
	APawn* ControllingPawn = AIController->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(ControllingPawn->GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;
	
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomReachablePointInRadius(ControllingPawn->GetActorLocation(), SearchRadius, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
