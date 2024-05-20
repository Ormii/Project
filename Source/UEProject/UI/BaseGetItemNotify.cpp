// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGetItemNotify.h"
#include "BaseItem.h"
#include "BaseAttackItem.h"
#include "BaseHealthItem.h"
#include "BaseBulletItem.h"
#include "BaseKeyItem.h"
#include "Survivor.h"
#include "InventoryComponent.h"
#include "PlayerController/BasePlayerController.h"


void UBaseGetItemNotify::Init(APawn *pSurvivor)
{
    SurvivorRef = Cast<ASurvivor>(pSurvivor);
    AlreadySeenItemTypes.Empty();
    pGetItem = nullptr;
}

void UBaseGetItemNotify::Release(void)
{
    pGetItem = nullptr;
}

bool UBaseGetItemNotify::IsItemAlreadySeen(EItemType nItemType)
{
    for(auto ntype : AlreadySeenItemTypes)
    {
        if(ntype == nItemType)
            return true;
    }

    return false;
}

bool UBaseGetItemNotify::AddItemAlreadySeen(ABaseItem* pItem)
{
    if(pItem == nullptr)
        return false;

    if(IsItemAlreadySeen(pItem->GetItemData().ItemType) == true)
        return false;

    AlreadySeenItemTypes.Add(pItem->GetItemData().ItemType);
    pGetItem = pItem;

    return true;
}

void UBaseGetItemNotify::NextActionStartEvent(void)
{
    SetVisibility(ESlateVisibility::Hidden);
    
    if(pGetItem != nullptr)
    {
        if(SurvivorRef)
        {
            int32 Remain = 0;
            bool IsSuccess = false;
            switch(pGetItem->GetItemData().ItemType)
            {
                case EItemType::EITEM_TYPE_DEFAULT_BULLET:
                    IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(Cast<ABaseBulletItem>(pGetItem), pGetItem->GetAmount(), Remain);
                    break;
                case EItemType::EITEM_TYPE_DEFAULT_HEALTHKIT:
                    IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(Cast<ABaseHealthItem>(pGetItem), pGetItem->GetAmount(), Remain);
                    break;
                case EItemType::EITEM_TYPE_DEFAULT_KEY:
                    IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(Cast<ABaseKeyItem>(pGetItem), pGetItem->GetAmount(), Remain);
                    break;
                case EItemType::EITEM_TYPE_DEFAULT_KNIFE:
                    IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(Cast<ABaseAttackItem>(pGetItem), pGetItem->GetAmount(), Remain);
                    break;
                case EItemType::EITEM_TYPE_DEFAULT_PISTOL:
                    IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(Cast<ABaseAttackItem>(pGetItem), pGetItem->GetAmount(), Remain);
                    break;
                default:
                    break;
            }

            if(IsSuccess)
            {
                if(Remain == 0)
                {
                    pGetItem->Destroy();
                }
                else
                {
                    pGetItem->SetAmount(Remain);
                }
            }

            SurvivorRef->GetSurvivorPlayerController()->SetIgnoreLookInput(false);
            SurvivorRef->InventoryActivate();
        }
    }
}
