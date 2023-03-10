
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_BossAttack.generated.h"

UCLASS()
class COMBAT_API UTask_BossAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	
public:

	UTask_BossAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AMyCharacter* Player{};
	class  ABossAIController* AIController{};
	APawn* Pawn{};
	class ABoss* Boss{};

	float Time{};
};
