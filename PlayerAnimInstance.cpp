#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (TryGetPawnOwner())
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}
