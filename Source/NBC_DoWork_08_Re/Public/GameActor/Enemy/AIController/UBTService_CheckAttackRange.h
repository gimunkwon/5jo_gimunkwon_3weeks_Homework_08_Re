#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UBTService_CheckAttackRange.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API UUBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
public:
	UUBTService_CheckAttackRange();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere,Category="AI")
	float AttackRange = 150.f;
};
