#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieAnimInst.generated.h"

class AMyZombie;

UCLASS()
class NBC_DOWORK_08_RE_API UZombieAnimInst : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Instance")
	TObjectPtr<AMyZombie> MyOwner;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Speed")
	float GroundSpeed;
};
