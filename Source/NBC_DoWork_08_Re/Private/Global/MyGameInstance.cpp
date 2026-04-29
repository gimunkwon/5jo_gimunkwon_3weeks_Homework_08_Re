#include "Global/MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	CurrentStageIndex = 1;
	bIsStarted = false;
}

void UMyGameInstance::InitializeGameInstanceValue()
{
	CurrentStageIndex = 1;
	bIsStarted = false;
}
