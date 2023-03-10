
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

UCLASS()
class COMBAT_API ABossAIController : public AAIController
{
	GENERATED_BODY()
	public:
	ABossAIController();
private:


	 class  AMyCharacter* Player{};
	 class  APawn* Pawn{};

protected:

	virtual void   BeginPlay()override;
	
	public:
	virtual void Tick(float DeltaSeconds) override;


public:
	void StartAttack();
	void StopAttack();
};
