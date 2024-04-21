// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_UpdatePlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor.h"

UBT_UpdatePlayerLocation::UBT_UpdatePlayerLocation()
{
    NodeName = TEXT("Update Player Location");
}

void UBT_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    ASurvivor* pSurvivor = Cast<ASurvivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    if(pSurvivor == NULL)
        return;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), pSurvivor->GetActorLocation());
}
