// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyFinishAttackAction.h"
#include "AnimNotifyFinishAttackAction.h"
#include "../Actor/Survivor.h"

void UAnimNotifyFinishAttackAction::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    ASurvivor *pSurvivor = Cast<ASurvivor>(MeshComp->GetOwner());
    if(pSurvivor == nullptr)
        return;

    pSurvivor->SetIsAttacking(false);
}