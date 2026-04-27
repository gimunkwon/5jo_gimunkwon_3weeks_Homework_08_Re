#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_AttackToPlayer.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API UBTT_AttackToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_AttackToPlayer();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
