#include "BossAttackControl.h"

#include "Boss.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBossAttackControl::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (ABoss* const Boss = Cast<ABoss>(MeshComp->GetOwner()))
	{
		
		Boss->bCanAttack = true;
		if (ABossAIController* const BossAIController = Cast<ABossAIController>(Boss->GetController()))
		{
			BossAIController->StartAttack();
			BossAIController->GetBlackboardComponent()->SetValueAsFloat("WaitTime",Animation->GetPlayLength());
		}
	}
}

void UBossAttackControl::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (ABoss* const Boss = Cast<ABoss>(MeshComp->GetOwner()))
	{
		Boss->bCanAttack = false;
		if (ABossAIController* const BossAIController = Cast<ABossAIController>(Boss->GetController()))
		{
			BossAIController->StopAttack();
			Boss->AttackIndex=-1;
		}
	}
}
