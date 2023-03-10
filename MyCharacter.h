#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class COMBAT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AMyCharacter();
protected:
	virtual void BeginPlay() override;
private:

	int Stamina{100};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
	UAnimMontage* RollMontage{};


	UPROPERTY(EditAnywhere)
	UAnimMontage* HitMontage{};

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimMontages{};
	


	void Attack();
	void DodgeRoll();
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE int GetHealth()const {return Health;}
	FORCEINLINE int GetStamina()const {return Stamina;}
	
	explicit operator int ()const
	{
		return Health;
	}
	UPROPERTY(EditAnywhere,Category="Sword")
	class ASword* Sword{};

	void TakeHammerDamage(const int Damage);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int Health{100};


	UPROPERTY(EditAnywhere)
	AActor* Boss{};
};
