#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIZombieController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;

UCLASS()
class NBC_DOWORK_08_RE_API AAIZombieController : public AAIController
{
	GENERATED_BODY()
public:
	AAIZombieController();
	FORCEINLINE const FDataTableRowHandle& GetRowHandle() {return RowHandle;}
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UBlackboardData> BB_Data;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UBehaviorTree> BT_Data;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	FDataTableRowHandle RowHandle;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
	
public:
	virtual void Tick(float DeltaTime) override;
};
