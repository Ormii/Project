// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseKeyItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "UI/BaseGetItemNotify.h"

ABaseKeyItem::ABaseKeyItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_KEY;
    ItemData.Name = "Key";
    ItemData.MaxStackAmount = 1;
    ItemData.CanbeUse = false;
    ItemData.CanbeEquiped = false;
}

void ABaseKeyItem::BeginPlay()
{
    Super::BeginPlay();
    
}

bool ABaseKeyItem::Interact(AActor *OtherActor)
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

bool ABaseKeyItem::UseItem()
{
    Super::UseItem();
    return true;
}