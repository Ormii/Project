// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyEndOverlap.h"
#include "Components/SphereComponent.h"
#include "Survivor.h"
#include "KnifeAttackItem.h"

void UAnimNotifyEndOverlap::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    ASurvivor *pSurvivor = Cast<ASurvivor>(MeshComp->GetOwner());
    if(pSurvivor == nullptr)
        return;

    if(pSurvivor->GetCurrentAttackItem() == nullptr)
        return;
    
    AKnifeAttackItem *pKnife = Cast<AKnifeAttackItem>(pSurvivor->GetCurrentAttackItem());
    if(pKnife == nullptr)
        return;

    if(pKnife->GetSphereComponent() == nullptr)
        return;
    
    pKnife->GetSphereComponent()->SetGenerateOverlapEvents(false);
}