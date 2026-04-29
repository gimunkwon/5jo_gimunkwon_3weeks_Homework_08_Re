#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/GunWeapon.h"
#include "MyPlayer.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class AGunWeapon;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EPlayerBattleState : uint8
{
	Melee,
	Gun
};


UCLASS()
class NBC_DOWORK_08_RE_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayer();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerBattleState GetPlayerBattleState() const {return PlayerBattleState;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbIsDead() const {return bIsDead;}

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AActor> MeleeWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AActor> GunWeapon;
	UPROPERTY()
	TMap<EPlayerBattleState, AActor*> WeaponMap;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animations")
	TObjectPtr<UAnimMontage> AM_MeleeAttack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animations")
	TObjectPtr<UAnimMontage> AM_GunAttack;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	float FireRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	float InterpSpeed;
	
#pragma region Movement
	void Move(const FInputActionValue& Value);
	void Rotate();
	void EndRotate();
#pragma endregion
#pragma region Weapon
	void InitializeWeapon(TSubclassOf<AActor> WeaponClass, EPlayerBattleState BattleState);
	void SelectWeapon(const FInputActionValue& Value);
	void Attack();
	void GunAttack(UAnimInstance* MyAnimInst);
	void MeleeAttack(UAnimInstance* MyAnimInst);
	UFUNCTION(BlueprintCallable)
	void CheckMeleeAttackRange();
	void CheckGunAttackRange(AGunWeapon* CurrentGunWeapon, FVector StartLocation, FVector EndLocation);
	void Reload();
	UFUNCTION()
	void EndAttackMontage(UAnimMontage* Montage, bool bIsEnd);
#pragma endregion 
	void OnDead();
	UFUNCTION(BlueprintCallable)
	void OnDeadAndAddWidget();
#pragma region Sound
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_GunFire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_MeleeAtt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_GunReload;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_GunDryFire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sound")
	TObjectPtr<USoundBase> Sound_Death;
#pragma endregion 
	
#pragma region Niagara
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Niagara")
	TObjectPtr<UNiagaraSystem> NS_MuzzleEffect;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NS_MuzzleEffectComp;
#pragma endregion 
	
private:
	EPlayerBattleState PlayerBattleState;
	bool bIsAttacking;
	bool bIsDead;
	
	float CurrentHP;
	float MaxHP;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
