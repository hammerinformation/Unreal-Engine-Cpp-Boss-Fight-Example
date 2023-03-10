#include "Task_MoveToPlayer.h"

#include "BossAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UTask_MoveToPlayer::UTask_MoveToPlayer()
{
	NodeName = "Task_MoveToPlayer";
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AIController == nullptr || Player == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UTask_MoveToPlayer::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	AIController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	Pawn = AIController->GetPawn();
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (AIController && Player)
	{
		//	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green, TEXT("AIController"));

		AIController->MoveToActor(Player, 10.f, true);

	
		const float Distance = AIController->GetBlackboardComponent()->GetValueAsFloat("PlayerDistance");
		if (Distance < 250.f)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
