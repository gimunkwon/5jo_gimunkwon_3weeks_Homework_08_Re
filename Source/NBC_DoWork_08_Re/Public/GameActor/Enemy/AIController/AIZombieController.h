#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIZombieController.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AAIZombieController : public AAIController
{
	GENERATED_BODY()
public:
	AAIZombieController();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UBlackboardData> BB_Data;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UBehaviorTree> BT_Data;
	
public:
	virtual void Tick(float DeltaTime) override;
};
