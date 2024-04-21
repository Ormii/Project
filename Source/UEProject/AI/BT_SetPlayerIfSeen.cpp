// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_SetPlayerIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor.h"
#include "AIController.h"

UBT_SetPlayerIfSeen::UBT_SetPlayerIfSeen()
{
    NodeName = TEXT("Update Player IfSeen");
}

void UBT_SetPlayerIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    
    ASurvivor* pSurvivor = Cast<ASurvivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if(pSurvivor == nullptr)
        return;

    AAIController *AIController = OwnerComp.GetAIOwner();
    if(AIController == nullptr)
        return;

    if(AIController->LineOfSightTo(pSurvivor))
    {  
        UE_LOG(LogTemp, Warning, TEXT("Find Survivor"));
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), pSurvivor);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UnFind Survivor"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
