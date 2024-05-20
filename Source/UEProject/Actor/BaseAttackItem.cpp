// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAttackItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "Compo/EquipComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "UI/BaseGetItemNotify.h"

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

		ABasePlayerController *pBasePlayerController = Survivor->GetSurvivorPlayerController();
		if(pBasePlayerController)
		{
			UBaseGetItemNotify *pGetItemNotifyWidget = pBasePlayerController->GetItemNotifyWidgetFunc();
			if(pGetItemNotifyWidget)
			{
				if(pGetItemNotifyWidget->AddItemAlreadySeen(this) == true)
				{
					pGetItemNotifyWidget->SetVisibility(ESlateVisibility::Visible);
					pGetItemNotifyWidget->InitGetItemNotify();
					pGetItemNotifyWidget->StartGetItemNotify();
					pBasePlayerController->SetIgnoreLookInput(true);
					pBasePlayerController->SetShowMouseCursor(true);
					Survivor->GetCharacterMovement()->DisableMovement();
				}
				else
				{
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
			}
		}
	}

    return true;
}

bool ABaseAttackItem::EquipItem()
{
	Super::EquipItem();
	UE_LOG(LogTemp, Warning, TEXT("Equip start"));

	if(Survivor)
	{
		int32 EmptyIndex = 0;
		UEquipComponent *Equipped = Survivor->GetEquipComponent();
		if(Equipped)
		{
			if(Equipped->CheckEmptySlot(EmptyIndex) == true)
			{
				ItemData.CanbeEquiped = false;
				ItemData.CanbeUnEquip = true;
				Equipped->SetEquipSlot(this,EmptyIndex);
			}
		}
	}

    return false;
}

bool ABaseAttackItem::UnEquipItem()
{
	Super::UnEquipItem();
	
	if(Survivor)
	{
		UEquipComponent *Equipped = Survivor->GetEquipComponent();
		auto EquipArray = Equipped->GetEquipArray();
		if(Equipped)
		{
			for(int i = 0; i < EquipArray.Num(); ++i)
			{
				if(EquipArray[i] == this)
				{
					ItemData.CanbeEquiped = true;
					ItemData.CanbeUnEquip = false;
					Equipped->RemoveEquipSlot(i);
					
					if(this == Survivor->GetCurrentAttackItem())
					{
						Survivor->SetCurrentAttackItem(nullptr);
					}
					return true;
				}
			}
		}
	}

	return false;
}

void ABaseAttackItem::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reload start"));
}
