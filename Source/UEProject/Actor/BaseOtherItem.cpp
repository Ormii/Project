// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "BaseOtherItem.h"

bool ABaseOtherItem::Interact(AActor *OtherActor)
{
    Super::Interact(OtherActor);
    if(Survivor)
	{
		Survivor->GetInventoryComponent()->AddItem(this, Amount);
	}

	Destroy();
    return false;
}

bool ABaseOtherItem::UseItem()
{
    Super::UseItem();
    return false;
}