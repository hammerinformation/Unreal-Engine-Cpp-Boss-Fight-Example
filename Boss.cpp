#include "Boss.h"

#include "BossAnimInstance.h"
#include "MyCharacter.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;
	BossUi = CreateDefaultSubobject<UWidgetComponent>(TEXT("Boss Ui"));
	HammerTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Hammer Trigger"));
	HammerTrigger->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "HammerCenter");
}


void ABoss::Attack()
{
	AttackIndex = FMath::RandRange(1, 4);
	bCanAttack = true;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	HammerTrigger->SetGenerateOverlapEvents(false);
	HammerTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABoss::OnComponentBeginOverlap);

	
}


void ABoss::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (AMyCharacter* const Player = Cast<AMyCharacter>(OtherActor))
	{
		Player->TakeHammerDamage(FMath::RandRange(15, 40));
	}
}

void ABoss::TakeSwordDamage(const int Damage)
{
	if (UBossAnimInstance* const PlayerAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		
		//if (HitReactFrontAnimMontage)
		if (HitReactFrontAnimMontage && PlayerAnimInstance->IsAnyMontagePlaying() == false)
		{
			PlayerAnimInstance->Montage_Play(HitReactFrontAnimMontage);
			Health -= Damage;
		}
	}
}
