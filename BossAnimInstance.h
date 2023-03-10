
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

UCLASS()
class COMBAT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	bool bCanAttack;
	UPROPERTY(BlueprintReadOnly)
	int AttackIndex{-1};

private:
	class ABoss* Boss{};
};
