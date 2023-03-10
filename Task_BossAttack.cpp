#include "Task_BossAttack.h"

#include "Boss.h"
#include "BossAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"

bool Attack = false;

UTask_BossAttack::UTask_BossAttack()
{
	NodeName = "Boss Attack";
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Attack = false;
	Time = {};
	if (!AIController || !Pawn || !Player || !Boss)
	{
		return EBTNodeResult::Aborted;
	}
	if (Boss)
	{
		Boss->Attack();
		Attack = true;
	}
	return EBTNodeResult::InProgress;
}

void UTask_BossAttack::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	AIController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	Pawn = AIController->GetPawn();
	Boss = Cast<ABoss>(Pawn);
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	Time += DeltaSeconds;
	Pawn->SetActorRotation(UKismetMathLibrary::REase(Pawn->GetActorRotation(),
	                                                 (Player->GetActorLocation() - Pawn->GetActorLocation()).
	                                                 Rotation(), DeltaSeconds * 2.f, true, EEasingFunc::Linear, 2, 2));
	if (Time > 1.76f)
	{
		Boss->AttackIndex = -1;
	}
	if (Attack && Boss->AttackIndex == -1)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
