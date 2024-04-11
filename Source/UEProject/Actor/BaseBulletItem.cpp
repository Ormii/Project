// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBulletItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"

ABaseBulletItem::ABaseBulletItem()
{
    ItemData.MaxStackAmount = 300;
}

bool ABaseBulletItem::Interact(AActor *OtherActor)
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

bool ABaseBulletItem::UseItem()
{
    Super::UseItem();
    return false;
}
