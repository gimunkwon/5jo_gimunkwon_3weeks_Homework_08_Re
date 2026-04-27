#pragma once

#include "CoreMinimal.h"
#include "DataTable/Weapon/DT_BaseWeapon.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"


UCLASS()
class NBC_DOWORK_08_RE_API AMyWeapon : public AActor
{
	GENERATED_BODY()
public:
	AMyWeapon();
	
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const {return StaticMeshComp;}
	FORCEINLINE float GetAttackDamage() const {return AttackDamage;}
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponStat")
	FDataTableRowHandle RowHandle;
	
	virtual void InitializeWeaponStat();
	
	FName WeaponName;
	float AttackDamage;
	
public:
	virtual void Tick(float DeltaTime) override;
};
