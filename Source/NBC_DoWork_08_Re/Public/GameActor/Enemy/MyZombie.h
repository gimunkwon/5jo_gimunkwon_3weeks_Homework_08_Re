#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyZombie.generated.h"

enum class EZombieType : uint8;
class UWidgetComponent;

UCLASS()
class NBC_DOWORK_08_RE_API AMyZombie : public ACharacter
{
	GENERATED_BODY()

public:
	AMyZombie();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<UWidgetComponent> WidgetC_EnemyStat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TObjectPtr<UDataTable> DT_Stat;
	
	void InitializeStat(EZombieType ZombieType);
	
private:
	float HP;
	float MaxHP;
	EZombieType ZombieTypes;
	
public:
	virtual void Tick(float DeltaTime) override;
};
