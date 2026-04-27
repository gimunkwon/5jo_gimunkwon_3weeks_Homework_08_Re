#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FindPlayerLocation.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API UBTT_FindPlayerLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_FindPlayerLocation();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere,Category="BlackBoard")
	FBlackboardKeySelector TargetLocationKey;
	UPROPERTY(EditAnywhere,Category="AI")
	float SearchRadius;
};
