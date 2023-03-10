
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class COMBAT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	ASword();

protected:
	virtual void BeginPlay() override;
public:
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Trigger{};
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SwordMesh{};

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound{};

	UFUNCTION()
			void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex,
				bool bFromSweep,
				const FHitResult& SweepResult);


	

};
