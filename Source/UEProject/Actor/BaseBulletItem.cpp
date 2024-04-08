// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBulletItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"

bool ABaseBulletItem::Interact(AActor *OtherActor)
{
    Super::Interact(OtherActor);
    if(Survivor)
	{
		Survivor->GetInventoryComponent()->AddItem(this, Amount);
	}

	Destroy();
    return false;
}

bool ABaseBulletItem::UseItem()
{
    Super::UseItem();
    return false;
}
