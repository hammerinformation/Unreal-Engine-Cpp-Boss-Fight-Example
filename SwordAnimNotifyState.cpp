

#include "SwordAnimNotifyState.h"

#include "MyCharacter.h"
#include "Sword.h"
#include "Components/BoxComponent.h"

void USwordAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (const AMyCharacter* const Player = Cast<AMyCharacter>(MeshComp->GetOwner()))
	{

		Player->Sword->Trigger->SetGenerateOverlapEvents(true);
	}}

void USwordAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (const AMyCharacter* const Player = Cast<AMyCharacter>(MeshComp->GetOwner()))
	{
		Player->Sword->Trigger->SetGenerateOverlapEvents(false);
	}
}
