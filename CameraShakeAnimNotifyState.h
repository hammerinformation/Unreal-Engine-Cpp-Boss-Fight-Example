
#pragma once

#include "CoreMinimal.h"
#include "MatineeCameraShake.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CameraShakeAnimNotifyState.generated.h"


UCLASS()
class COMBAT_API UCameraShakeAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf< UMatineeCameraShake> CameraShake;
};
