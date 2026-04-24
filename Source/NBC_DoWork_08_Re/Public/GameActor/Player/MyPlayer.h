#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

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
	
	float LastFireTime;
	
	void Move(const FInputActionValue& Value);
	void InitializeWeapon(TSubclassOf<AActor> WeaponClass, EPlayerBattleState BattleState);
	void SelectWeapon(const FInputActionValue& Value);
	void Attack();
	void GunAttack(UAnimInstance* MyAnimInst);
	void MeleeAttack(UAnimInstance* MyAnimInst);
	void Reload();
	
	UFUNCTION()
	void EndAttackMontage(UAnimMontage* Montage, bool bIsEnd);
	
private:
	EPlayerBattleState PlayerBattleState;
	bool bIsAttacking;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
