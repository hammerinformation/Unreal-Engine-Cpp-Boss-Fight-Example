#include "BossAnimInstance.h"

#include "Boss.h"

void UBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Boss = Cast<ABoss>(TryGetPawnOwner());
}
void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (TryGetPawnOwner())
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
		if (Boss)
		{
			AttackIndex=Boss->AttackIndex;
			bCanAttack = Boss->bCanAttack;
		}
	}
}


