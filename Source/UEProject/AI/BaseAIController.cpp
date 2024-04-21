// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseAIController.h"
#include "Survivor.h"

void ABaseAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsObject(TEXT("Self"),this);
        GetBlackboardComponent()->SetValueAsVector(TEXT("SelfLocation"),GetPawn()->GetActorLocation());
    }
}

void ABaseAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
