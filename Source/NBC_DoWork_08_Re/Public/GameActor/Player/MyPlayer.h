#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

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
	EPlayerBattleState GetPlayerBattleState() const {return PlayerBattleState;}
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
	
private:
	EPlayerBattleState PlayerBattleState;
	bool bIsAttacking;
	
	float CurrentHP;
	float MaxHP;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
