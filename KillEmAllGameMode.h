// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntergalacticGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INTERGALACTIC_API AKillEmAllGameMode : public AIntergalacticGameModeBase
{
	GENERATED_BODY()

public:
	void PawnKilled(APawn* Pawn) override;

private:
	void EndGame(bool IsPlayerWinner);
};
