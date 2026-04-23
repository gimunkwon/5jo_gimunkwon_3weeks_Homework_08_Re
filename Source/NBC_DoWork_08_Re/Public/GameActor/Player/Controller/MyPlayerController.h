#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class NBC_DOWORK_08_RE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_Move;
	
protected:
	virtual void BeginPlay() override;
};
