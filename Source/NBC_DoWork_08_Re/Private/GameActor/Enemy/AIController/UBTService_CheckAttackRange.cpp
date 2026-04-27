#include "GameActor/Enemy/AIController/UBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTService_CheckAttackRange::UUBTService_CheckAttackRange()
{
	NodeName = TEXT("Check Attack Range");
	Interval = 0.2f;
}

void UUBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController* AIC = OwnerComp.GetAIOwner();
	APawn* ControllingPawn = AIC->GetPawn();
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	
	if (ControllingPawn && TargetActor)
	{
		float Distance = FVector::Dist(ControllingPawn->GetActorLocation(), TargetActor->GetActorLocation());
		
		bool bInRange = (Distance <= AttackRange);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bCanAttackRange"), bInRange);
	}
	
}
