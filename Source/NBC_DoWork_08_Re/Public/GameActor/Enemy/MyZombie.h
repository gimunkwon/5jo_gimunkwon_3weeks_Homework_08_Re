#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyZombie.generated.h"

class UWidgetComponent;

UCLASS()
class NBC_DOWORK_08_RE_API AMyZombie : public ACharacter
{
	GENERATED_BODY()

public:
	AMyZombie();
	
	void AttackToPlayer(AActor* Attacked_Actor);
	void InitializeStat(const FDataTableRowHandle& RowHandle);
	
	UFUNCTION(BlueprintCallable)
	void ZombieAttackHitCheck();
	
	FORCEINLINE float GetAttackRange() const {return AttackRange;}
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<UWidgetComponent> WidgetC_EnemyStat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> Widget_EnemyStat;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animations")
	TObjectPtr<UAnimMontage> AM_Dead;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animations")
	TObjectPtr<UAnimMontage> AM_Attack;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_ZombieAtt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_ZombieDeath;
	
	void OnDead();
private:
	float HP;
	float MaxHP;
	float AttackRange;
	
public:
	virtual void Tick(float DeltaTime) override;
};
