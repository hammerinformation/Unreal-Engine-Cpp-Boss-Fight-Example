#include "MyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PlayerAnimInstance.h"
#include "Sword.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 100.0f;
	GetCharacterMovement()->AirControl = 0.2f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 90.f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Sword)
	{
		Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Hand_RSocket");

		Sword->SetActorRelativeLocation(FVector(-50.030231f, -10.246703f, 29.603924f));
		Sword->SetActorRelativeRotation(FRotator(40.391857f, 77.168091f, -39.656437f));
		Sword->Trigger->SetGenerateOverlapEvents(false);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		                                 FString{"Health"} + FString::Printf(TEXT("%d"), static_cast<int>(*this)));
	}


}


void AMyCharacter::Attack()
{
	if (UPlayerAnimInstance* const PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		UAnimMontage* const AttackAnimMontage = AttackAnimMontages[FMath::RandRange(0, AttackAnimMontages.Num() - 1)];
		GetCharacterMovement()->MaxWalkSpeed = 0;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
		}), AttackAnimMontage->GetPlayLength(), false);
		if (AttackAnimMontage && PlayerAnimInstance->IsAnyMontagePlaying() == false)
		{
			PlayerAnimInstance->Montage_Play(AttackAnimMontage);
		}
	}
}

void AMyCharacter::DodgeRoll()
{
	if (UPlayerAnimInstance* const PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (RollMontage && PlayerAnimInstance->IsAnyMontagePlaying() == false)
		{
			PlayerAnimInstance->Montage_Play(RollMontage);
		}
	}
}

void AMyCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AMyCharacter::DodgeRoll);
	PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AMyCharacter::TakeHammerDamage(const int Damage)
{
	if (UPlayerAnimInstance* const PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (HitMontage && PlayerAnimInstance->IsAnyMontagePlaying() == false)
		{
			if (Boss)
			{
				const FVector ForwardVector = GetActorForwardVector();
				const FVector TargetLocation = Boss->GetActorLocation() - GetActorLocation();
				const float DotProduct = FVector::DotProduct(ForwardVector.GetUnsafeNormal(),
				                                             TargetLocation.GetUnsafeNormal());
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Dot: %f"), DotProduct));
				if (DotProduct > 0.1f)
				{
					GetCharacterMovement()->MaxWalkSpeed = 0;
					GetCharacterMovement()->RotationRate.Yaw = 0;
					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
					{
						GetCharacterMovement()->MaxWalkSpeed = 600.f;
						GetCharacterMovement()->RotationRate.Yaw = 540.f;

					}), HitMontage->GetPlayLength(), false);

					PlayerAnimInstance->Montage_Play(HitMontage);
				}
			}


			Health -= Damage;
			if (Health <= 0)
			{
				Health = 0;
			}
		}
	}
}
