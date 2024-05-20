// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHealthItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "UI/BaseGetItemNotify.h"

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

bool ABaseHealthItem::UseItem()
{
    Super::UseItem();
    
    return true;
}