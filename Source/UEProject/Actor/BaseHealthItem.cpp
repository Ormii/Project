// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"

ABaseHealthItem::ABaseHealthItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_HEALTHKIT;
    ItemData.Name = "Health Kit";
    ItemData.MaxStackAmount = 10;
    ItemData.CanbeUse = true;
    ItemData.CanbeEquiped = false;
}

void ABaseHealthItem::BeginPlay()
{
    Super::BeginPlay();
    
}

bool ABaseHealthItem::Interact(AActor *OtherActor)
{
    Super::Interact(OtherActor);
    if(Survivor)
	{
        int32 Remain = 0;
		bool IsSuccess = Survivor->GetInventoryComponent()->AddItem(this, Amount, Remain);
        if(IsSuccess)
        {
            if(Remain == 0)
            {
                Destroy();
            }
            else
            {
                SetAmount(Remain);
            }
        }
    }

    return false;
}

bool ABaseHealthItem::UseItem()
{
    Super::UseItem();
    
    return true;
}