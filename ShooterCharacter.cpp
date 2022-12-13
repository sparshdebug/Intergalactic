// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "IntergalacticGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AShooterCharacter::TurnRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AShooterCharacter::ShiftPressed);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AShooterCharacter::ShiftReleased);
	PlayerInputComponent->BindAction(TEXT("Trigger"), IE_Pressed, this, &AShooterCharacter::TriggerPressed);
	PlayerInputComponent->BindAction(TEXT("Trigger"), IE_Released, this, &AShooterCharacter::TriggerReleased);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	
	if (IsDead())
	{
		AIntergalacticGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AIntergalacticGameModeBase>();
		if (GameMode != nullptr) 
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::TurnRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::ShiftPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AShooterCharacter::ShiftReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AShooterCharacter::TriggerPressed()
{
	Gun->PullTrigger(true);
}

void AShooterCharacter::TriggerReleased()
{
	Gun->PullTrigger(false);
}


