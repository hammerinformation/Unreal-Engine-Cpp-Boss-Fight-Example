#include "BossAIController.h"

#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ABossAIController::ABossAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Pawn = GetPawn();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		if (Player)
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Player);
		}
	}), 1.0f, false);
}

void ABossAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetBlackboardComponent()->SetValueAsFloat("PlayerDistance",
	                                          FVector::Distance(Pawn->GetActorLocation(), Player->GetActorLocation()));
}

void ABossAIController::StartAttack()
{
	GetBlackboardComponent()->SetValueAsBool("InAttack", true);
}

void ABossAIController::StopAttack()
{
	GetBlackboardComponent()->SetValueAsBool("InAttack", false);
}
