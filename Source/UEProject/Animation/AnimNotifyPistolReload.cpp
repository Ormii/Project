// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyPistolReload.h"
#include "AnimNotifyPistolReload.h"
#include "../Actor/Survivor.h"
#include "../Actor/PistolAttackItem.h"

void UAnimNotifyPistolReload::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    ASurvivor *pSurvivor = Cast<ASurvivor>(MeshComp->GetOwner());
    if(pSurvivor == nullptr)
        return;

    if(pSurvivor->GetCurrentAttackItem() == nullptr)
        return;

    switch(pSurvivor->GetCurrentAttackItem()->GetItemData().ItemType)
    {
        case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
        {
            APistolAttackItem *pPistolAtkItem = Cast<APistolAttackItem>(pSurvivor->GetCurrentAttackItem());
            pPistolAtkItem->Reload();
        }
            break;
        default:
            break;
    }
}