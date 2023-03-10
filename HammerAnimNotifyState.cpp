#include "HammerAnimNotifyState.h"

#include "Boss.h"
#include "Components/BoxComponent.h"

void UHammerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (const ABoss* const Boss = Cast<ABoss>(MeshComp->GetOwner()))
	{

		Boss->HammerTrigger->SetRelativeScale3D(TriggerScale);
		Boss->HammerTrigger->SetGenerateOverlapEvents(true);
	}
}

void UHammerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (const ABoss* const Boss = Cast<ABoss>(MeshComp->GetOwner()))
	{
		Boss->HammerTrigger->SetRelativeScale3D(FVector::OneVector * 4);

		Boss->HammerTrigger->SetGenerateOverlapEvents(false);
	}
}
