// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "BaseKeyItem.h"

bool ABaseKeyItem::Interact(AActor *OtherActor)
{
    Super::Interact(OtherActor);
    if(Survivor)
	{
		Survivor->GetInventoryComponent()->AddItem(this, 1);
	}

	Destroy();
    return false;
}

bool ABaseKeyItem::UseItem()
{
    Super::UseItem();
    return false;
}