#include "GameActor/Enemy/AIController/AIZombieController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"


AAIZombieController::AAIZombieController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	SightConfig->SightRadius = 700.f;
	SightConfig->LoseSightRadius = 1000.f;
	SightConfig->PeripheralVisionAngleDegrees = 120.f;
	SightConfig->SetMaxAge(5.f);
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIZombieController::OnTargetPerceived);
	
}


void AAIZombieController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIZombieController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (RunBehaviorTree(BT_Data))
	{
		UE_LOG(LogTemp,Warning,TEXT("비헤이비어트리 작동"));
	}
}

void AAIZombieController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SightConfig)
	{
		DrawDebugSphere(GetWorld(),GetPawn()->GetActorLocation(), SightConfig->SightRadius,32,FColor::Green, false, -1.f, 0, 1.f);
		DrawDebugSphere(GetWorld(),GetPawn()->GetActorLocation(), SightConfig->LoseSightRadius,32,FColor::Red, false, -1.f, 0, 1.f);
	}
}


void AAIZombieController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag(TEXT("Player")))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp,Warning,TEXT("플레이어 발견"));
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("플레이어 놓침"));
			GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
		}
	}
}



