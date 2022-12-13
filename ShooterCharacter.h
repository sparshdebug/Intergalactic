// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class INTERGALACTIC_API AShooterCharacter : public ACharacter
{
	
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void TriggerPressed();
	void TriggerReleased();

private:

	float SprintSpeed = 600.f;
	float WalkSpeed = 400.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float Health;

	void MoveForward(float AxisValue);
	void TurnRight(float AxisValue);
	void ShiftPressed();
	void ShiftReleased();


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
