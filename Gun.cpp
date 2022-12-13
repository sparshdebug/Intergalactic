// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGun::PullTrigger(bool bTriggerLoop)
{
	GetWorldTimerManager().SetTimer(FireRateTimer, this, &AGun::Shot,FireRate, bTriggerLoop, 0.f);
}

void AGun::Shot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, "MuzzleFlash");

	FHitResult Hit;
	FVector HitDirection;
	bool bSuccess = GunTrace(Hit, HitDirection);
	
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpact,Hit.Location, HitDirection.Rotation());
		
		
		AActor* HitActor = Hit.GetActor();
		if (Hit.GetActor() != nullptr) 
		{
			FPointDamageEvent DamageEvent(Damage, Hit, HitDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector HitDirection)
{
	FVector Location;
	FRotator Rotation;
	GetOwnerController()->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * Length;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(Door->)
	HitDirection = -Rotation.Vector();
	
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End,
	 ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}