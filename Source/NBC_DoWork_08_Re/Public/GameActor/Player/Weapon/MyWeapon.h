#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class NBC_DOWORK_08_RE_API AMyWeapon : public AActor
{
	GENERATED_BODY()
public:
	AMyWeapon();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
public:
	virtual void Tick(float DeltaTime) override;
};
