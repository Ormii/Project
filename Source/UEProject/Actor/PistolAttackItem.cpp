// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PistolAttackItem.h"
#include "PistolAttackItem.h"

APistolAttackItem ::APistolAttackItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_PISTOL;
    ItemData.Name = "Pistol";
    ItemData.MaxStackAmount = 1;
	ItemData.CanbeUse = false;
	ItemData.CanbeEquiped = true;
	ItemData.CanbeUnEquip = false;

}
void APistolAttackItem::BeginPlay()
{
    Super::BeginPlay();
}