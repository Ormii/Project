// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBulletItem.h"
#include "Actor/Survivor.h"
#include "Compo/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "UI/BaseGetItemNotify.h"

ABaseBulletItem::ABaseBulletItem()
{
    ItemData.ItemType = EItemType::EITEM_TYPE_DEFAULT_BULLET;
    ItemData.Name = "Bullet";
    ItemData.CanbeUse = false;
    ItemData.CanbeEquiped = false;
    ItemData.MaxStackAmount = 300;
}

void ABaseBulletItem::BeginPlay()
{
    Super::BeginPlay();
}

bool ABaseBulletItem::Interact(AActor *OtherActor)
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

bool ABaseBulletItem::UseItem()
{
    Super::UseItem();
    return false;
}
