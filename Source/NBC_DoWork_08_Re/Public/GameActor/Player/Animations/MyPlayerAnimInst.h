#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInst.generated.h"

enum class EPlayerBattleState : uint8;
class AMyPlayer;

UCLASS()
class NBC_DOWORK_08_RE_API UMyPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Instance")
	TObjectPtr<AMyPlayer> MyOwnerInst;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="State")
	EPlayerBattleState CurrentBattleState;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Speed")
	float PlayerSpeed;
};
