// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGetItemNotify.h"
#include "BaseItem.h"
#include "Survivor.h"
#include "InventoryComponent.h"


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

    AlreadySeenItemTypes.Add(pItem->GetItemData().ItemType);
    pGetItem = pItem;

    return false;
}


void UBaseGetItemNotify::NextActionStartEvent(void)
{
    SetVisibility(ESlateVisibility::Hidden);

    if(pGetItem != nullptr)
    {
        if(SurvivorRef)
        {
            int32 Remain = 0;
            bool IsSuccess = SurvivorRef->GetInventoryComponent()->AddItem(pGetItem, pGetItem->GetAmount(), Remain);
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
        }
    }
}
