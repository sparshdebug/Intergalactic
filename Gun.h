// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class INTERGALACTIC_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

void PullTrigger(bool bTriggerLoop);
void Shot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float Length = 1000;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitImpact;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 0.5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Door;

	FTimerHandle FireRateTimer;

	bool GunTrace(FHitResult& Hit, FVector HitDirection);

	AController* GetOwnerController() const;
};
