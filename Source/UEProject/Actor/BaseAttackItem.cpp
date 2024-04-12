// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAttackItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"

ABaseAttackItem::ABaseAttackItem()
{
	ItemData.MaxStackAmount = 1;
	ItemData.CanbeUse = false;
	ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;
}

void ABaseAttackItem::BeginPlay()
{
	Super::BeginPlay();
}

bool ABaseAttackItem::Interact(AActor *OtherActor)
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

bool ABaseAttackItem::EquipItem()
{
	Super::EquipItem();
	ItemData.CanbeEquiped = false;
	ItemData.CanbeUnEquip = true;

	if(Survivor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Equip start"));
		switch(ItemData.ItemType)
		{
			case EItemType::EITEM_TYPE_DEFAULT_KNIFE:
				Survivor->SetEquipedType(EEquipedType::EQUIPED_TYPE_KNIFE);
				break;
			case EItemType::EITEM_TYPE_DEFAULT_GUN:
				Survivor->SetEquipedType(EEquipedType::EQUIPED_TYPE_PISTOL);
				break;
			default:
				break;
		}

		Survivor->GetAnim
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Survivor not setted"));
	}

    return true;
}

bool ABaseAttackItem::UnEquipItem()
{
	Super::UnEquipItem();
    ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;
	
	
	if(Survivor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnEquip start"));
		Survivor->SetEquipedType(EEquipedType::EQUIPED_TYPE_UNARMED);
	}
	return true;
}
