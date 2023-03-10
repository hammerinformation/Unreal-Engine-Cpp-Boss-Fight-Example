
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class COMBAT_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	ABoss();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int Health{100};
	int Stamina{100};


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bCanAttack;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int AttackIndex{-1};

	UPROPERTY(EditAnywhere)
	UAnimMontage* HitReactFrontAnimMontage{};

	void TakeSwordDamage(const int Damage);

	UPROPERTY(EditAnywhere)
	class UBoxComponent* HammerTrigger{};

	
	void Attack();

protected:
	virtual void BeginPlay() override;


	class UWidgetComponent* BossUi{};

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);


	
};
