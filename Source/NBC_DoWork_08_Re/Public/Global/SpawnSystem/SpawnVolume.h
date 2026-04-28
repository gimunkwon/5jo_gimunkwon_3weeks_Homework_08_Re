#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

#define MAXVOLUMECOUNT 3

enum class EZombieType : uint8;
class UBoxComponent;

UCLASS()
class NBC_DOWORK_08_RE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();
	void InitializeSpawnPool(int32 WaveIndex);
	void SpawnZombieInVolume(int32 WaveIndex);
	int32 GetSpawnCount(int32 WaveIndex);
	int32 GetSpawnIndex() const {return WaveIndexValue;}
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Collision")
	TObjectPtr<UBoxComponent> BoxCollisionComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	TObjectPtr<UDataTable> DT_SpawnValue;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieActor")
	TArray<TSubclassOf<AActor>> ZombieActor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ZombieData")
	TArray<FName> ZombieDTRow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WaveIndex")
	int32 WaveIndexValue;
	
	FVector RandomSpawnPoint();
	void CreatePool(const TMap<EZombieType, int32>& SpawnCountMap, TArray<AActor*>& SpawnPool);
private:
	UPROPERTY()
	TArray<AActor*> Wave1_Pool;
	UPROPERTY()
	TArray<AActor*> Wave2_Pool;
	UPROPERTY()
	TArray<AActor*> Wave3_Pool;
public:
	virtual void Tick(float DeltaTime) override;
};
