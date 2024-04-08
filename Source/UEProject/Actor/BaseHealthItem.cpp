// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"

bool ABaseHealthItem::Interact(AActor *OtherActor)
{
    Super::Interact(OtherActor);
    if(Survivor)
	{
		Survivor->GetInventoryComponent()->AddItem(this, Amount);
	}

	Destroy();
    return false;
}

bool ABaseHealthItem::UseItem()
{
    Super::UseItem();
    return false;
}