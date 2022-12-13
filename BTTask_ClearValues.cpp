// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearValues.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearValues::UBTTask_ClearValues()
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearValues::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
    Super::ExecuteTask(OwnerComp, NodeMemory);
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}
