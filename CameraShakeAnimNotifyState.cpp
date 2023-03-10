#include "CameraShakeAnimNotifyState.h"

#include "Kismet/GameplayStatics.h"

void UCameraShakeAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	const UWorld* const World = MeshComp->GetWorld();

	if (World)
	{
		APlayerCameraManager* const PlayerCameraManager = World->GetFirstPlayerController()->PlayerCameraManager;
		if (PlayerCameraManager)
		{
			PlayerCameraManager->StartCameraShake(CameraShake, 1.0f);
		}
	}
}
