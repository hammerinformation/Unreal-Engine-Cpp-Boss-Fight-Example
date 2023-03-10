#include "Sword.h"

#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ASword::ASword()
{
	PrimaryActorTick.bCanEverTick = true;
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	RootComponent = SwordMesh;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(GetRootComponent());
}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnComponentBeginOverlap);
}

void ASword::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (ABoss* Boss = Cast<ABoss>(OtherActor))
	{
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, this->GetActorLocation());
		}

		Boss->TakeSwordDamage(FMath::RandRange(5, 10));
	}
}
