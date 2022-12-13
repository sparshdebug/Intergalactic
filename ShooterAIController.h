#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

UCLASS()
class INTERGALACTIC_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
};
