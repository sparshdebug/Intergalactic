// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if (AIBehavior != nullptr)
    RunBehaviorTree(AIBehavior);

    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControllerCharacted = Cast<AShooterCharacter>(GetPawn());
    if (ControllerCharacted != nullptr)
    {
        return ControllerCharacted->IsDead();
    }
    return true;
}
