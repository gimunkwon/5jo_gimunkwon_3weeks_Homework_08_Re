#pragma once

#include "CoreMinimal.h"
#include "DT_ZombieStat.generated.h"


UENUM(BlueprintType)
enum class EZombieType : uint8
{
	Normal,
	Running,
	Boss,
};


USTRUCT(BlueprintType)
struct FZombieStat : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	EZombieType ZombieType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float MaxHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float MaxWalkSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float AttackRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float AttackDamage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float SightRadius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float LoseSightRadius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float SightDegrees;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	FVector AttackBoxSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieStat")
	float AttackDetectionRange;
};
