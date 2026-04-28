#pragma once

#include "CoreMinimal.h"
#include "DataTable/Zombie/DT_ZombieStat.h"
#include "DT_SpawnZombie.generated.h"


USTRUCT(BlueprintType)
struct FSpawnZombie : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnCount")
	TMap<EZombieType,int32> Wave1_SpawnCount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnCount")
	TMap<EZombieType,int32> Wave2_SpawnCount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpawnCount")
	TMap<EZombieType,int32> Wave3_SpawnCount;
};
