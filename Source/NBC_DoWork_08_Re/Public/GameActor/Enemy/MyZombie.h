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
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<UWidgetComponent> WidgetC_EnemyStat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> Widget_EnemyStat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	FDataTableRowHandle RowHandle;
	
	void InitializeStat();
	
private:
	float HP;
	float MaxHP;
	
public:
	virtual void Tick(float DeltaTime) override;
};
