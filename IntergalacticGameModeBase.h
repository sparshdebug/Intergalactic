// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IntergalacticGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INTERGALACTIC_API AIntergalacticGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* Pawn);

};
